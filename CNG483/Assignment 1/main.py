# Mert Can Bilgin - 2453025

from PIL import Image
import os
import cv2
import numpy as np
import matplotlib.pyplot as plt

# -------- PART 1 --------

# Open original images using PIL
original_1 = Image.open('Dataset/original_1.jpeg')
original_2 = Image.open('Dataset/original_2.jpeg')

# Define scaling factor and angle for rotation
scale_factor = 3
rotation_angle = 45

# Define the new dimensions for scaling for image 1
new_width_1 = original_1.width * scale_factor
new_height_1 = original_1.height * scale_factor

# Define the new dimensions for scaling for image 2
new_width_2 = original_2.width * scale_factor
new_height_2 = original_2.height * scale_factor

# Scale original images
scaled_1= original_1.resize((new_width_1, new_height_1))
scaled_2 = original_2.resize((new_width_2, new_height_2))

# Rotate original images
rotated_1 = original_1.rotate(45)
rotated_2 = original_2.rotate(45)

# Save scaled and rotated images
output_directory = 'Dataset/'

# Save scaled images
scaled_1.save(os.path.join(output_directory, 'scaled_1.jpeg'))
scaled_2.save(os.path.join(output_directory, 'scaled_2.jpeg'))

# Save rotated images
rotated_1.save(os.path.join(output_directory, 'rotated_1.jpeg'))
rotated_2.save(os.path.join(output_directory, 'rotated_2.jpeg'))


# -------- PART 2 --------
# Generate SIFT features for an image
def generate_sift_features(image):
    sift = cv2.SIFT_create()
    keypoints, descriptors = sift.detectAndCompute(image, None)
    return keypoints, descriptors


# Match keypoints between two images, and filter matches using the Lowe's ratio test
def match_keypoints(descriptors1, descriptors2):
    flann = cv2.DescriptorMatcher_create(cv2.DescriptorMatcher_FLANNBASED)
    matches = flann.knnMatch(descriptors1, descriptors2, k=2)
    ratio_thresh = 0.7
    good_matches = []
    for m, n in matches:
        if m.distance < ratio_thresh * n.distance:
            good_matches.append(m)
    return good_matches


# Display top matched keypoints
def display_top_matched_keypoints(image1, keypoints1, image2, keypoints2, matches, num_matches=10):
    matches = sorted(matches, key=lambda x: x.distance)
    image_matches = cv2.drawMatches(image1, keypoints1, image2, keypoints2, matches[:num_matches], None, flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
    plt.imshow(image_matches)
    plt.axis('off')
    plt.show()


# Plot matching distance
def plot_matching_distance(matches):
    # Sort matches based on distance
    matches_sorted = sorted(matches, key=lambda x: x.distance)
    num_matches = min(len(matches_sorted), 10)  # Limit to top 10 matches
    distances = [match.distance for match in matches_sorted[:num_matches]]
    indices = range(num_matches)
    plt.plot(indices, distances, marker='o', linestyle='-')
    plt.xlabel('Keypoint Index')
    plt.ylabel('Matching Distance')
    plt.title('Matching Distance for Top 10 Matched Keypoints')
    plt.show()


# Store all images as np array
images = [np.array(original_1), np.array(scaled_1), np.array(rotated_1), np.array(original_2), np.array(scaled_2), np.array(rotated_2)]

# Generate SIFT features for all images
keypoints = []
descriptors = []
for image in images:
    kp, desc = generate_sift_features(image)
    keypoints.append(kp)
    descriptors.append(desc)

# Match keypoints of each original image to transformed images
matches = []
matches.append(match_keypoints(descriptors[0], descriptors[1]))
matches.append(match_keypoints(descriptors[0], descriptors[2]))
matches.append(match_keypoints(descriptors[3], descriptors[4]))
matches.append(match_keypoints(descriptors[3], descriptors[5]))

# Display the top ten matched keypoints for each pair of images and plot matching distance
# Original 1 and Scaled 1
display_top_matched_keypoints(images[0], keypoints[0], images[1], keypoints[1], matches[0])
plot_matching_distance(matches[0])

# Original 1 and Rotated 1
display_top_matched_keypoints(images[0], keypoints[0], images[2], keypoints[2], matches[1])
plot_matching_distance(matches[1])

# Original 2 and Scaled 2
display_top_matched_keypoints(images[3], keypoints[3], images[4], keypoints[4], matches[2])
plot_matching_distance(matches[2])

# Original 2 and Rotated 2
display_top_matched_keypoints(images[3], keypoints[3], images[5], keypoints[5], matches[3])
plot_matching_distance(matches[3])

"""
f) Discuss the effect of increasing/decreasing the scale on the matching distance.
=> When we increase the scale factor, we make the image bigger. It means the keypoints in the
scaled image is also be bigger. These bigger keypoints cause more matches because they are more
distinctive. However, it can also cause to decrease on the matching distance because the relative
distances between keypoints decrease.
=> When we decrease the scale factor, we make the image smaller. It may cause to detect
fewer key points, so there may be fewer matches. However, it leads to increase the 
matching distance because the relative distances between key points increase.

g) Discuss the effect of increasing/decreasing the rotation on the matching distance.
=> When we increase the angle of rotation, we make the keypoints being detected in different
spatial locations. If keypoints are detected in different locations, it might result
fewer matches and an increase in matching distance.
=> Because SIFT is rotation-invariant, small rotation angles may not significantly change
the result. Therefore, the matching distance may remain stable.
"""
