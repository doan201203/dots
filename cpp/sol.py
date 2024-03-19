def pow(a, b):
    if b == 0:
        return 1
    if b % 2 == 0:
        y = pow(a, b//2)
        return y * y
    y = pow(a, (b - 1) // 2)
    return a * y * y
print(pow(3, 3))
