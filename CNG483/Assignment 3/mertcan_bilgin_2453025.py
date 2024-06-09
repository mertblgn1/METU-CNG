"""
I've chosen learning rate as 0.0001 in order to ensure the model converges steadily.
Even though the training might take longer, we minimize the risk of overshooting.
Also, I've chosen 50 as the number of epochs because it is the best option according to
the plots. I've also chosen regularization strength as 0.01 to prevent overfitting.

Effects of the Number of Layers:
The simpler architecture allows for faster training and fewer parameters, which can be
beneficial when working with smaller datasets. The loss and accuracy curves for this 2 layers
network showed steady improvement over epochs. In the three-layer network, it has more capacity
to learn complex patterns. However, it has a risk of overfitting.

Effects of the number of Neurons in the Hidden Layers
100 neurons allow the network to capture a wider range of features. Reducing the number
of neurons in the subsequent layer helps in progressively learning while reducing the
model's complexity. Further reduction allows for even more campact feature representations.
"""


import os
import cv2
import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt

# Set a seed for reproducibility
torch.manual_seed(42)
np.random.seed(42)


def imageLoaderAndFeatureExtractor(training_path, testing_path, image_size=(32, 32)):
    # Dictionary to hold features and labels
    data = {
        'train': {'features': [], 'labels': []},
        'test': {'features': [], 'labels': []}
    }

    # Define the class labels
    class_labels = {'building': 0, 'forest': 1, 'glacier': 2}

    # Helper function to process images
    def process_images(path, data_type):
        for class_name in class_labels:
            class_folder = os.path.join(path, class_name)
            label = class_labels[class_name]
            for image_name in os.listdir(class_folder):
                image_path = os.path.join(class_folder, image_name)
                image = cv2.imread(image_path)
                if image is not None:
                    # Resize image
                    resized_image = cv2.resize(image, image_size)
                    # Flatten the image to a 1D array
                    feature_vector = resized_image.flatten()
                    # Append to data dictionary
                    data[data_type]['features'].append(feature_vector)
                    data[data_type]['labels'].append(label)

    # Process training and testing images
    process_images(training_path, 'train')
    process_images(testing_path, 'test')

    # Convert lists to numpy arrays
    train_features = np.array(data['train']['features'])
    train_labels = np.array(data['train']['labels'])
    test_features = np.array(data['test']['features'])
    test_labels = np.array(data['test']['labels'])

    return (train_features, train_labels), (test_features, test_labels)


def setFormer(train_features, train_labels, validation_split=0.25):
    # Convert to numpy arrays for easier indexing
    train_features = np.array(train_features)
    train_labels = np.array(train_labels)

    # Create empty list for validation sets
    val_features = []
    val_labels = []

    # Get unique classes
    classes = np.unique(train_labels)

    for cls in classes:
        # Get indices of all images of this class
        cls_indices = np.where(train_labels == cls)[0]
        # Shuffle indices to ensure random split
        np.random.shuffle(cls_indices)

        # Calculate the number of validation samples
        val_size = int(len(cls_indices) * validation_split)

        # Split indices into validation
        val_indices = cls_indices[:val_size]

        # Append validation data
        val_features.extend(train_features[val_indices])
        val_labels.extend(train_labels[val_indices])

    # Convert lists back to numpy array
    val_features = np.array(val_features)
    val_labels = np.array(val_labels)

    return (train_features, train_labels), (val_features, val_labels)


# Define the first neural network with 2 hidden layers
class TwoLayerNN(nn.Module):
    def __init__(self, input_size, hidden_size1, hidden_size2, num_classes):
        super(TwoLayerNN, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size1)
        self.relu1 = nn.ReLU()
        self.fc2 = nn.Linear(hidden_size1, hidden_size2)
        self.relu2 = nn.ReLU()
        self.fc3 = nn.Linear(hidden_size2, num_classes)

    def forward(self, x):
        out = self.fc1(x)
        out = self.relu1(out)
        out = self.fc2(out)
        out = self.relu2(out)
        out = self.fc3(out)
        return out


# Initialize the neural network
input_size = 32 * 32 * 3
hidden_size1 = 100
hidden_size2 = 50
num_classes = 3
model1 = TwoLayerNN(input_size, hidden_size1, hidden_size2, num_classes)

# Define the hyperparameters
learning_rate = 0.0001
num_epochs = 50
batch_size = 64
regularization_strength = 0.01

# Define the loss function and optimizer
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(model1.parameters(), lr=learning_rate, weight_decay=regularization_strength)


# Train the model
def train(model, criterion, optimizer, train_loader, val_loader, num_epochs):
    train_losses = []
    val_losses = []
    train_accs = []
    val_accs = []
    for epoch in range(num_epochs):
        model.train()
        running_loss = 0.0
        correct_train = 0
        total_train = 0
        for images, labels in train_loader:
            images = images.float()
            images = images.view(-1, 32 * 32 * 3)
            optimizer.zero_grad()
            outputs = model(images)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()
            running_loss += loss.item()
            _, predicted = torch.max(outputs.data, 1)
            total_train += labels.size(0)
            correct_train += (predicted == labels).sum().item()
        train_loss = running_loss / len(train_loader)
        train_acc = correct_train / total_train
        train_losses.append(train_loss)
        train_accs.append(train_acc)

        # Validation
        model.eval()
        val_loss = 0.0
        correct_val = 0
        total_val = 0
        with torch.no_grad():
            for images, labels in val_loader:
                images = images.float()
                images = images.view(-1, 32 * 32 *3)
                outputs = model(images)
                loss = criterion(outputs, labels)
                val_loss += loss.item()
                _, predicted = torch.max(outputs.data, 1)
                total_val += labels.size(0)
                correct_val += (predicted == labels).sum().item()
        val_loss /= len(val_loader)
        val_acc = correct_val / total_val
        val_losses.append(val_loss)
        val_accs.append(val_acc)
        print('Epoch [{}/{}], Train Loss: {:.4f}, Train Acc: {:.4f}, Val Loss: {:.4f}, Val Acc: {:.4f}'
              .format(epoch + 1, num_epochs, train_loss, train_acc, val_loss, val_acc))

    return train_losses, val_losses, train_accs, val_accs


# Define the second neural network with 3 hidden layers
class ThreeLayerNN(nn.Module):
    def __init__(self, input_size, hidden_size1, hidden_size2, hidden_size3, num_classes):
        super(ThreeLayerNN, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size1)
        self.relu1 = nn.ReLU()
        self.fc2 = nn.Linear(hidden_size1, hidden_size2)
        self.relu2 = nn.ReLU()
        self.fc3 = nn.Linear(hidden_size2, hidden_size3)
        self.relu3 = nn.ReLU()
        self.fc4 = nn.Linear(hidden_size3, num_classes)

    def forward(self, x):
        out = self.fc1(x)
        out = self.relu1(out)
        out = self.fc2(out)
        out = self.relu2(out)
        out = self.fc3(out)
        out = self.relu3(out)
        out = self.fc4(out)
        return out


# Initialize the neural network
hidden_size3 = 20
model2 = ThreeLayerNN(input_size, hidden_size1, hidden_size2, hidden_size3, num_classes)

# Define the loss function and optimizer
optimizer2 = optim.SGD(model2.parameters(), lr=learning_rate, weight_decay=regularization_strength)


training_path = 'TrainingSet'
testing_path = 'TestingSet'
(train_features, train_labels), (test_features, test_labels) = imageLoaderAndFeatureExtractor(training_path, testing_path)
(train_features, train_labels), (val_features, val_labels) = setFormer(train_features, train_labels)

# Train the first neural network (model1)
train_loader = torch.utils.data.DataLoader(torch.utils.data.TensorDataset(torch.tensor(train_features), torch.tensor(train_labels)), batch_size=batch_size, shuffle=True)
val_loader = torch.utils.data.DataLoader(torch.utils.data.TensorDataset(torch.tensor(val_features), torch.tensor(val_labels)), batch_size=batch_size, shuffle=False)

train_losses1, val_losses1, train_accs1, val_accs1 = train(model1, criterion, optimizer, train_loader, val_loader, num_epochs)

# Train the second neural network (model2)
train_losses2, val_losses2, train_accs2, val_accs2 = train(model2, criterion, optimizer2, train_loader, val_loader, num_epochs)


# Evaluate both models on the testing data
def evaluate(model, test_features, test_labels):
    model.eval()
    with torch.no_grad():
        images = torch.tensor(test_features, dtype=torch.float32).view(-1, 32 * 32 * 3)
        outputs = model(images)
        _, predicted = torch.max(outputs.data, 1)

        # Convert test_labels to a PyTorch tensor
        test_labels_tensor = torch.tensor(test_labels)

        # Ensure that predicted labels have the same data type as test_labels_tensor
        predicted = predicted.type_as(test_labels_tensor)

        total = test_labels_tensor.size(0)
        correct = (predicted == test_labels_tensor).sum().item()
        accuracy = correct / total
        print('Testing Accuracy: {:.4f}'.format(accuracy))


# Evaluate model1
print("Model 1:")
evaluate(model1, test_features, test_labels)

print("Model 2:")
# Evaluate model2
evaluate(model2, test_features, test_labels)

# Plot the loss curves
# First model
plt.figure(figsize=(10, 5))
plt.plot(range(num_epochs), train_losses1, label='Training Loss')
plt.plot(range(num_epochs), val_losses1, label='Validation Loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.title('Loss Curve')
plt.legend()
plt.show()

# Second model
plt.figure(figsize=(10, 5))
plt.plot(range(num_epochs), train_losses2, label='Training Loss')
plt.plot(range(num_epochs), val_losses2, label='Validation Loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.title('Loss Curve')
plt.legend()
plt.show()

# Plot the accuracy curves
# First model
plt.figure(figsize=(10, 5))
plt.plot(range(num_epochs), train_accs1, label='Training Accuracy')
plt.plot(range(num_epochs), val_accs1, label='Validation Accuracy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.title('Accuracy Curve - Two Layer NN')
plt.legend()
plt.show()

# Second model
plt.figure(figsize=(10, 5))
plt.plot(range(num_epochs), train_accs2, label='Training Accuracy')
plt.plot(range(num_epochs), val_accs2, label='Validation Accuracy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.title('Accuracy Curve - Three Layer NN')
plt.legend()
plt.show()