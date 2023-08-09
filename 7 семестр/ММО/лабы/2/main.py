import pandas as pd
from sklearn import tree
from sklearn.model_selection import train_test_split

if __name__ == '__main__':
    clf = pd.read_csv('heart_data.csv', header=None)
    clf = clf.replace("?", None)

    x = clf.loc[1:, 0:12]
    y = clf.loc[1:, 13]
    clf = tree.DecisionTreeClassifier(random_state=0, max_depth=12, max_leaf_nodes=2)

    print(' N \t\t На обучающей', 'На тестовой', sep=" ")
    for i in range(10):
        X_train, X_test, Y_train, Y_test = train_test_split(x, y, test_size=0.3)
        clf.fit(X_train, Y_train)
        print(f'{(i + 1):2} {clf.score(X_train, Y_train) :15.6f} {clf.score(X_test, Y_test) :15.6f}')

