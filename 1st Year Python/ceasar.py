def caesar_cipher(message, shift):
    encrypted_message = ""
    for char in message:
        if char.isalpha():
            shifted_char = chr((ord(char) - 97 + shift) % 26 + 97)
            encrypted_message += shifted_char
        else:
            encrypted_message += char
    return encrypted_message

message = input("Enter message: ")
shift = int(input("Enter shift value: "))

encrypted_message = caesar_cipher(message, shift)

print("Message:", encrypted_message)



