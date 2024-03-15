import json
import cv2
import numpy as np


def load_ships():
    metadata = __get_metadata()
    image = __get_assets()
    ship_list = []
    for _, ship_data in metadata.items():
        ship_list.append({
            "type": ship_data["type"],
            "size": ship_data["size"],
            "image": __load_ship_by_location(image,
                                             ship_data["location"]["point_1"],
                                             ship_data["location"]["point_2"])
        })


def __get_metadata():
    metadata_filename = 'metadata.json'
    try:
        with open(metadata_filename, 'r') as file:
            ships_metadata = json.loads(file.read())
            return ships_metadata
    except Exception:
        raise FileExistsError("Failed To Load Metadata")


def __get_assets():
    asset_filename = 'battleship_assets.png'
    image = cv2.imread(asset_filename)
    if image is None:
        raise FileNotFoundError("Failed To Load Assets")
    return image


def __load_ship_by_location(image, point1, point2):
    vector1 = np.array([point1["x"], point1["y"]])
    vector2 = np.array([point2["x"], point2["y"]])
    direction_vector = vector2 - vector1
    width = int(abs(direction_vector[0]))
    height = int(abs(direction_vector[1]))
    aspect_ratio = max(width, height) / min(width, height)

    if aspect_ratio > 1:  # Wider than tall, rotate for vertical alignment
        rotation_angle = np.arctan2(direction_vector[1], direction_vector[0])
    else:  # Taller than wide, rotate for horizontal alignment
        rotation_angle = np.arctan2(-direction_vector[1], -direction_vector[0]) + np.pi / 2

    translation = vector1

    # Get the image dimensions for transformation matrix creation
    rows, cols, _ = image.shape

    # Define the rotation matrix
    rotation_matrix = cv2.getRotationMatrix2D((cols / 2, rows / 2), np.rad2deg(rotation_angle), 1.0)

    # Combine rotation and translation using shift matrix
    translation_matrix = np.vstack([rotation_matrix, [translation[0], translation[1], 1]])

    # Apply transformations (rotation and translation)
    rotated_image = cv2.warpAffine(image, translation_matrix, (cols, rows))

    # Calculate new image dimensions based on the bounding box
    new_width = min(width, height)
    new_height = min(width, height)

    # Get the center coordinates of the rotated image
    center_x = int(cols / 2)
    center_y = int(rows / 2)

    # Crop the rotated image to get a square (considering potential margins)
    start_x = max(0, center_x - int(new_width / 2))
    start_y = max(0, center_y - int(new_height / 2))
    end_x = min(cols, center_x + int(new_width / 2))
    end_y = min(rows, center_y + int(new_height / 2))
    squared_image = rotated_image[start_y:end_y, start_x:end_x]

    cv2.imshow("", squared_image)

load_ships()