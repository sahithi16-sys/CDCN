def character_count(frames):
    return "".join(str(len(f)+1)+f for f in frames)

def decode_character_count(s):
    out,i=[],0
    while i<len(s):
        n = int(s[i])
        out.append(s[i+1:i+n])
        i+=n
    return out

FLAG,ESC = "FLAG","ESC"

def character_stuff(data):
    words = data.split()
    out=[]
    for w in words:
        if w in (FLAG,ESC):
          out.append(ESC)
        out.append(w)
    return " ".join([FLAG] + out + [FLAG])

def character_destuff(f):
    frames = f.split()[1:-1]
    out,i=[],0

    while i<len(frames):
        if frames[i]==ESC:
            i+=1
        out.append(frames[i])
        i+=1
    return " ".join(out)

def bit_stuff(bits):
    out,count="",0

    for b in bits:
        out+=b
        if b=="1":
            count+=1
            if count==5:
                out+="0"
                count=0
        else:
            count=0
    return "0111110" + out + "01111110"

def bit_destuff(f):
    data = f[8:-8]
    out,i,count="",0,0

    while i<len(data):
        out += data[i]
        if data[i]=="1":
            count+=1
            if count==5:
                i+=1
                count=0
        else:
            count=0
        i+=1
    return out

frames = input("Enter frames : ").split()
s = character_count(frames)
print("Character count : ",s)
print("Decoded : ",decode_character_count(s))

data = input("Enter Data : ")
f = character_stuff(data)
print("Character Stuffing : ",f)
print("Decoded : ", character_destuff(f))

bits = input("Enter bits : ")
f = bit_stuff(bits)
print("Bit Stuffing : ",f)
print("Decoded : ",bit_destuff(f))