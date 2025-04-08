def encrypt_message(message, shift):
    encrypted_message = ""
    for char in message:
        if char.isalpha():
            shifted_char = chr((ord(char) - 97 + shift) % 26 + 97)
            encrypted_message += shifted_char
        else:
            encrypted_message += char
    return encrypted_message
def decrypt_message(message, shift):
    decrypted_message = ""
    for char in message:
        if char.isalpha():
            shifted_char = chr((ord(char) - 97 - shift) % 26 + 97)
            decrypted_message += shifted_char
        else:
            decrypted_message += char
    return decrypted_message
message = input("Enter a message to encrypt: ")
shift = int(input("Enter a shift value: "))
encrypted_message = encrypt_message(message, shift)
print("Encrypted message: ", encrypted_message)
encrypted_message = input("Enter a message to decrypt: ")
shift = int(input("Enter the shift value used to encrypt the message: "))
decrypted_message = decrypt_message(encrypted_message, shift)
print("Decrypted message: ", decrypted_message)