import os
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
from skimage.feature import hog
from skimage.transform import resize
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import LabelEncoder


def load_images_from_folder(folder, image_size=(128, 128)):
    images = []
    labels = []
    for class_name in os.listdir(folder):
        class_path = os.path.join(folder, class_name)
        if os.path.isdir(class_path):
            for filename in os.listdir(class_path):
                img_path = os.path.join(class_path, filename)
                try:
                    img = Image.open(img_path).convert('L')  # Convert image to grayscale
                    img = resize(np.array(img), image_size)
                    images.append(np.array(img))
                    labels.append(class_name)
                except Exception as e:
                    print(f"Error loading image {img_path}: {e}")
    return images, labels


def hist_features(images, num_bins=256):
    hist_features = []
    for img in images:
        # Convert image to grayscale
        if len(img.shape) == 3:
            img = np.array(Image.fromarray(img).convert('L'))

        # Compute histogram
        hist, _ = np.histogram(img.flatten(), bins=num_bins, range=(0, 256))
        hist_features.append(hist)
    return np.array(hist_features)


"""
HOG captures local gradient information in an image by dividing it into small cells and computing histograms of gradient
orientations within each cell. This allows it to capture edge and texture information. HOG features are robust to
changes in lighting conditions because they are based on local gradient information rather than absolute pixel values.
This makes HOG features suitable for this assignment where lighting variations are common, such as outdoor scene
classification like building, forest, and glacier.
"""
def mystery_features(images, orientations=9, pixels_per_cell=(8, 8), cells_per_block=(3, 3)):
    features = []
    for img in images:
        # Compute HOG features for the image
        hog_features = hog(img, orientations=orientations, pixels_per_cell=pixels_per_cell,
                           cells_per_block=cells_per_block, transform_sqrt=True, block_norm="L2-Hys")
        features.append(hog_features)
    return np.array(features)


def split_train_validation(train_images, train_labels, validation_ratio=0.25):
    val_images = []
    val_labels = []

    # Get unique class labels
    unique_labels = np.unique(train_labels)

    # Iterate over each class label
    for label in unique_labels:
        # Find indices of images with the current label
        label_indices = [i for i, l in enumerate(train_labels) if l == label]

        # Calculate the number of images for validation
        num_val_images = int(len(label_indices) * validation_ratio)

        # Take the first 'num_val_images' images for validation
        val_indices = label_indices[:num_val_images]

        # Add images and labels to the validation set
        val_images.extend([train_images[i] for i in val_indices])
        val_labels.extend([train_labels[i] for i in val_indices])

    return val_images, val_labels


def training(train_features, train_labels, val_features, val_labels):
    """
    Train KNN classifier with different values of K and evaluate accuracy on validation set.

    Parameters:
    - train_features: Training features (histogram or HOG features).
    - train_labels: Class labels for training set.
    - val_features: Validation features (histogram or HOG features).
    - val_labels: Class labels for validation set.

    Returns:
    - best_k: The best value of K based on validation accuracy.
    """

    # Define a range of K values to try
    k_values = [1, 3, 5, 7]

    # Initialize lists to store accuracy for each value of K
    accuracies = []

    # Iterate over each value of K
    for k in k_values:
        # Create KNN classifier with current value of K
        knn = KNeighborsClassifier(n_neighbors=k, metric='l1')

        # Train the classifier on training data
        knn.fit(train_features, train_labels)

        # Predict labels for validation set
        val_pred = knn.predict(val_features)

        # Calculate accuracy
        accuracy = accuracy_score(val_labels, val_pred)

        # Append accuracy to list
        accuracies.append(accuracy)

    # Plot accuracy vs. K
    plt.plot(k_values, accuracies, marker='o')
    plt.title('Accuracy vs. K Value')
    plt.xlabel('K Value')
    plt.ylabel('Accuracy')
    plt.grid(True)
    plt.show()

    # Find the best K value (maximum accuracy)
    best_k = k_values[np.argmax(accuracies)]
    print("Best K value:", best_k)

    return best_k


def testing(best_k, train_features, train_labels, test_features, test_labels):
    """
    Test the trained KNN classifier on the testing set and display the classification accuracy.

    Parameters:
    - best_k: The best value of K returned by the training function.
    - train_features: Training features (histogram or HOG features).
    - train_labels: Class labels for training set.
    - test_features: Testing features (histogram or HOG features).
    - test_labels: Class labels for testing set.
    """

    # Create KNN classifier with best K-value
    knn = KNeighborsClassifier(n_neighbors=best_k, metric='l1')

    # Train the classifier on training data
    knn.fit(train_features, train_labels)

    # Predict labels for testing set
    test_pred = knn.predict(test_features)

    # Calculate accuracy
    accuracy = accuracy_score(test_labels, test_pred)
    print("Classification Accuracy on Testing Set:", accuracy)


def main():
    # Load training set
    train_folder = "TrainingSet"
    train_images, train_labels = load_images_from_folder(train_folder)

    # Load testing set
    test_folder = "TestingSet"
    test_images, test_labels = load_images_from_folder(test_folder)

    # Extract histogram features for training and testing sets
    hist_features_training = hist_features(train_images)
    hist_features_testing = hist_features(test_images)

    # Save the features
    np.save('hist_features_training.npy', hist_features_training)
    np.save('hist_features_testing.npy', hist_features_testing)

    # Extract mystery features for training and testing sets
    mystery_features_training = mystery_features(train_images)
    mystery_features_testing = mystery_features(test_images)

    # Save the features
    np.save('mystery_features_training.npy', mystery_features_training)
    np.save('mystery_features_testing.npy', mystery_features_testing)

    # Form validation set
    val_images, val_labels = split_train_validation(train_images, train_labels)

    # Extract histogram features for validation set
    hist_features_validation = hist_features(val_images)
    np.save('hist_features_validation.npy', hist_features_validation)

    # Extract mystery features for validation set
    mystery_features_validation = mystery_features(val_images)
    np.save('mystery_features_validation.npy', mystery_features_validation)

    # Encode class labels to integers for mystery_features
    label_encoder = LabelEncoder()
    train_labels_encoded = label_encoder.fit_transform(train_labels)
    val_labels_encoded = label_encoder.transform(val_labels)
    test_labels_encoded = label_encoder.fit_transform(test_labels)

    print("Best K-Value for hist_features and testing:")
    # Best K-Value for hist_features
    best_k = training(mystery_features_training, train_labels_encoded, mystery_features_validation, val_labels_encoded)
    # Testing for hist_features
    testing(best_k, hist_features_training, train_labels, hist_features_testing, test_labels)

    print("Best K-Value for mystery_features and testing:")
    # Best K-Value for mystery_features
    best_k = training(mystery_features_training, train_labels_encoded, mystery_features_validation, val_labels_encoded)
    # Testing for mystery_features
    testing(best_k, mystery_features_training, train_labels_encoded, mystery_features_testing, test_labels_encoded)


if __name__ == "__main__":
    main()
