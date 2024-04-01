import os
import cv2
import numpy as np

class ThresholdModel:  
    def __init__(self, images_path: str, annotations_path: str) -> None:
        self.label_colors = dict()
        self.threshold = dict()
        self.images_path = images_path
        self.annotations_path = annotations_path
    
    def __handle_image(self, image_name: str, annotation_name: str, label_name: str):
        image = cv2.imread(os.path.join(self.images_path, image_name))
        annotation = cv2.imread(os.path.join(self.annotations_path, annotation_name))
        
        intensity = image[np.where(np.all(annotation == self.label_colors[label_name], axis=2))]
        return (intensity[:, 0], intensity[:, 1], intensity[:, 2])
        
    def add_label(self, label_name: str, label_color: list) -> None:
        self.label_colors[label_name] = label_color
        self.threshold[label_name] = {
            'min': [0, 0, 0],
            'max': [0, 0, 0]
        }
    
    def fit(self, images_name: list[str], annotations_name: list[str]) -> None:
        self.threshold['DiaChua']['min'] = [40.38468533476484, 49.240048946486034, 53.96235322041261]
        self.threshold['DiaChua']['max'] = [101.66640524609224, 114.69617353040124, 121.78266246017313]
        self.threshold['VungVoKhuan']['min'] = [32.2084267449019, 39.6612831004534, 44.30325282389873]
        self.threshold['VungVoKhuan']['max'] = [65.21472150134665, 76.36149918574242, 79.72290027683793]
        self.threshold['GiayKhangSinh']['min'] = [126.60285822121041, 140.2869895548091, 146.46139839088465]
        self.threshold['GiayKhangSinh']['max'] = [210.7803239464768, 222.3998203893222, 228.6677646895513]
    def predict(self, image: np.ndarray, label: str) -> np.ndarray:
        mask = image.copy()
        pos = (self.threshold[label]['min'] <= mask).all(axis=2) & (mask <= self.threshold[label]['max']).all(axis=2)
        mask[np.where(pos)] = self.label_colors[label]
        mask[np.where(np.logical_not(pos))] = [0, 0, 0]
        return mask