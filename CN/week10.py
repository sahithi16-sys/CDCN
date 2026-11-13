POLYNOMIALS = {
    "CRC-12": "1100000001111",
    "CRC-16": "11000000000000101",
    "CRC-CCITT": "10001000000100001"
}

def text_to_bits(text):
    return "".join(format(ord(c), "08b") for c in text)

def xor(a, b):
    return "".join("0" if x == y else "1"
                   for x, y in zip(a, b))

def mod2_div(dividend, divisor):
    n = len(divisor)
    rem = dividend[:n]

    for i in range(n, len(dividend) + 1):
        if rem[0] == "1":
            rem = xor(rem, divisor)
        else:
            rem = xor(rem, "0" * n)

        rem = rem[1:]

        if i < len(dividend):
            rem += dividend[i]

    return rem

def crc_encode(bits, poly):
    r = len(poly) - 1
    crc = mod2_div(bits + "0" * r, poly)
    return crc, bits + crc

def crc_check(codeword, poly):
    return "1" not in mod2_div(codeword, poly)


data = input("Enter data (characters): ")
bits = text_to_bits(data)

print("Data in binary :", bits)

for name, poly in POLYNOMIALS.items():
    crc, code = crc_encode(bits, poly)

    print("\n----", name, "----")
    print("Generator      :", poly)
    print("CRC bits       :", crc)
    print("Transmitted    :", code)

    print("Receiver check :", "No error" if crc_check(code, poly)
            else "Error detected")

    bad = code[:3] + ("1" if code[3] == "0" else "0") + code[4:]

    print("Bit 4 flipped :", "No error" if crc_check(bad, poly)
            else "Error detected")