import json
import cv2
import numpy as np


def load_ships():
    metadata = __get_metadata()
    assets, board = __get_assets()
    ship_list = []
    for _, ship_data in metadata.items():
        ship_list.append({
            "type": ship_data["type"],
            "size": ship_data["size"],
            "image": __load_ship_by_location(assets,
                                             ship_data["location"]["point_1"],
                                             ship_data["location"]["point_2"])
        })

    return ship_list, board


def __get_metadata():
    metadata_filename = 'assets/metadata.json'
    try:
        with open(metadata_filename, 'r') as file:
            ships_metadata = json.loads(file.read())
            return ships_metadata
    except Exception:
        raise FileExistsError("Failed To Load Metadata")


def __get_assets():
    asset_filename = 'assets/battleship_assets.png'
    board_filename = 'assets/board.png'
    assets, board = cv2.imread(asset_filename), cv2.imread(board_filename)
    if assets is None or board is None:
        raise FileNotFoundError("Failed To Load Assets")
    return assets, board


def __load_ship_by_location(image, point1, point2):
    upper_left = np.array([point1["x"], point1["y"]])
    lower_right = np.array([point2["x"], point2["y"]])
    roi = image[upper_left[1]:lower_right[1], upper_left[0]:lower_right[0]]
    return roi


load_ships()
