#this isnt mine
def xor_split(s, key=0x4A, chunk_s=8):
    xored = bytes([b ^ key for b in s.encode()])
    chunks = [xored[i:i + chunk_s] for i in range(0, len(xored), chunk_s)]

    c_chunks = []
    for chunk in chunks:
        hex_str = ''.join(f'\\x{b:02X}' for b in chunk)
        c_chunks.append(f'"{hex_str}"')

    # Print all at once (not inside the loop!)
    print("\nchar *obfuscated[] = {")
    for c in c_chunks:
        print(f"    {c},")
    print("};")
    print(f"int obfuscated_len = {len(xored)};")
    print(f"int xor_key = 0x{key:X};\n")

    return c_chunks, key

if __name__ == "__main__":
    inpt = input("input >:")
    xor_split(inpt)
