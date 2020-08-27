def     simplex(array, product):
    while countNeg(array) > 0:
        pivot = getPivot(array)
        if pivot[0] == -1 or pivot[1] == -1:
            return
        setPivot(array, pivot[0], pivot[1])
        if pivot[1] in range(len(product)):
            product[pivot[1]] = pivot[0]
        else:
            product[pivot[1] % len(product)] = pivot[0]


def     countNeg(array):
    count = 0
    ymax = len(array)
    xmax = len(array[0])

    for x in range(xmax):
        if array[ymax - 1][x] < 0:
            count += 1

    return count

def     getPivot(array):
    minimum = float("inf")
    ymax = len(array)
    xmax = len(array[0])
    ypiv = -1
    xpiv = -1

    for x in range(xmax):
        if array[ymax - 1][x] < minimum:
            minimum = array[ymax - 1][x]
            xpiv = x

    minimum = float("inf")

    for y in range(ymax - 1):
        if array[y][xpiv] != 0 and array[y][xmax - 1] / array[y][xpiv] > 0 and array[y][xmax - 1] / array[y][xpiv] < minimum:
            minimum = array[y][xmax - 1] / array[y][xpiv]
            ypiv = y

    return (ypiv, xpiv)


def     setPivot(array, ypiv, xpiv):
    xmax = len(array[0])
    div = array[ypiv][xpiv]
    ymax = len(array)

    if div == 0:
        return

    for x in range(xmax):
        array[ypiv][x] /= div

    for y in range(ymax):
        if y != ypiv:
            mult = -array[y][xpiv]
            for x in range(xmax):
                array[y][x] += (mult * array[ypiv][x])
