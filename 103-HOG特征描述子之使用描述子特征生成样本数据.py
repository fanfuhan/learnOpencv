"""
HOG特征描述子之使用描述子特征生成样本数据
"""

import cv2 as cv
import os
import numpy as np


def get_hog_descriptor(image):
    hog = cv.HOGDescriptor()
    h, w = image.shape[:2]
    # 预处理输入图像
    rate = 64 / w
    image = cv.resize(image, (64, np.int(rate * h)))
    gray = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
    bg = np.zeros((128, 64), dtype=np.uint8)
    bg[:,:] = 127
    h, w = gray.shape
    dy = (128 - h) // 2
    bg[dy:h+dy,:] = gray
    cv.waitKey(0)
    # 64x128 = 3780
    fv = hog.compute(bg, winStride=(8, 8), padding=(0, 0))
    return fv


def generate_dataset(pdir, ndir):
    train_data = []
    labels = []
    for file_name in os.listdir(pdir):
        img_dir = os.path.join(pdir, file_name)
        img = cv.imread(img_dir)
        hog_desc = get_hog_descriptor(img)
        one_fv = np.zeros([len(hog_desc)], dtype=np.float32)
        for i in range(len(hog_desc)):
            one_fv[i] = hog_desc[i][0]
        train_data.append(one_fv)
        labels.append(1)

    for file_name in os.listdir(ndir):
        img_dir = os.path.join(ndir, file_name)
        img = cv.imread(img_dir)
        hog_desc = get_hog_descriptor(img)
        one_fv = np.zeros([len(hog_desc)], dtype=np.float32)
        for i in range(len(hog_desc)):
            one_fv[i] = hog_desc[i][0]
        train_data.append(one_fv)
        labels.append(-1)
    return np.array(train_data, dtype=np.float32), np.array(labels, dtype=np.int32)


if __name__ == '__main__':
    generate_dataset("images/elec_watch/positive/",
                     "images/elec_watch/negative/")
    cv.destroyAllWindows()
