def getSoLanXuatHien(s:str):
    mp , tong = dict(), 0
    for i in s.strip().split():
        tong += 1
        if i in mp:
            mp[i] += 1
        else:
            mp[i] = 1
    
    ret = ''
    for i in mp:
        ret += 'p({}): {:.2f}%, '.format(i[0], mp[i]/tong*100)
    
    return ret[:len(ret)-2]

if __name__ == '__main__':
    s = str(input("Nhap vao xau s").strip())
    print(getSoLanXuatHien(s))
    