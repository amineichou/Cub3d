import struct

# Desired sum for hashcode
target = 0x21DD09EC  # 567797884

# Brute-force search to find the correct passcode
def find_passcode():
    part = 113559576  # Starting point for the first four parts

    # We'll assume the first four integers are the same and find the last one
    for last_part in range(0, 0xFFFFFFFF):
        if 4 * part + last_part == target:
            return struct.pack('<5I', part, part, part, part, last_part)

    return None

correct_passcode = find_passcode()

if correct_passcode:
    # print("Found correct passcode:", correct_passcode.hex())
    print(correct_passcode.decode('latin1'))
else:
    print("Failed to find a correct passcode.")
