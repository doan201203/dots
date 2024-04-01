import json
import numpy as np
import pandas as pd

def read_json(filepath):
    with open(filepath, 'r') as f:
        return json.loads(f.read())

data = read_json('/home/trdoan20/dev/cpp/CV/annotations/instances_default.json')
annotations = data['annotations']

anns_DiaChua = list(filter(lambda ann: ann['category_id'] == 1, data['annotations']))
anns_VungVoKhuan = list(filter(lambda ann: ann['category_id'] == 2, data['annotations']))
anns_GiayKhangSinh = list(filter(lambda ann: ann['category_id'] == 3, data['annotations']))

print(*[ann['bbox'][3] for ann in anns_GiayKhangSinh], sep='\n')

r_VungVoKhuan = np.array([(ann['bbox'][2] + ann['bbox'][3]) / 4 for ann in anns_VungVoKhuan])
r_GiayKhangSinh = np.array([(ann['bbox'][2] + ann['bbox'][3]) / 4 for ann in anns_GiayKhangSinh])

print('Số lượng ảnh là %d' % (len(data['images'])))
print('Số lượng labels của DiaChua là %d' % (len(anns_DiaChua)))
print('Số lượng labels của VungVoKhuan là %d' % (len(anns_VungVoKhuan)))
print('Số lượng labels của GiayKhangSinh là %d' % (len(anns_GiayKhangSinh)))

print('Bán kính trung bình của VungVoKhuan là %.2f' % (r_VungVoKhuan.mean()))
print('Bán kính trung bình của GiayKhangSinh là %.2f' % (r_GiayKhangSinh.mean()))

print('Độ lệch chuẩn bán kính của VungVoKhuan là %.2f' % (r_VungVoKhuan.std()))
print('Độ lệch chuẩn bán kính của GiayKhangSinh là %.2f' % (r_GiayKhangSinh.std()))

print('Phương sai bán kính của VungVoKhuan là %.2f' % (r_VungVoKhuan.var()))
print('Phương sai bán kính của GiayKhangSinh là %.2f' % (r_GiayKhangSinh.var()))