import random
from tensorflow import metrics
from tensorflow.keras.datasets import cifar10
from sklearn.preprocessing import StandardScaler
from tensorflow.keras import models, layers, constraints
from tensorflow.keras import utils
from keras.constraints import maxnorm
from tensorflow.keras.datasets import boston_housing
import scipy
from sklearn.preprocessing import StandardScaler
from tensorflow.keras import models, layers

(X_train, y_train), (X_test, y_test) = boston_housing.load_data(seed=1)
# print(X_train[0], y_train[0])
scaler = StandardScaler()
scaler.fit(X_train)
X_train_scaled = scaler.transform(X_train)
X_test_scaled = scaler.transform(X_test)
# print(X_train_scaled[0])

model = models.Sequential()
model.add(layers.Dense(64, activation='relu', input_shape=[X_train.shape[1]]))
model.add(layers.GaussianDropout(0.2))
model.add(layers.Dense(64, activation='relu'))
model.add(layers.GaussianDropout(0.2))
model.add(layers.Dense(1))

model.compile(optimizer='adam', loss='mse', metrics=['mae', 'accuracy'])
# model.compile(optimizer='sgd', loss='mse', metrics=['mae'])
model.fit(X_train_scaled, y_train, validation_split=0.2, epochs=500, batch_size=32)
model.evaluate(X_test_scaled, y_test)

num = 10;
to_predict = X_test_scaled[:num]
predictions = model.predict(to_predict)


print("Предсказанная цена и фактическая")
print("predict    Заданные значения");
for i in range(num):
    print('%.2f$ ~ %.2f$' %(predictions[i]*1000, y_test[i]*1000))

# print(X_test_scaled.shape)
# to_predict_sum = X_test_scaled
# predictions_sum = model.predict(to_predict_sum)
# print("Проц = ", metrics.mean_absolute_error(y_test, predictions_sum))
