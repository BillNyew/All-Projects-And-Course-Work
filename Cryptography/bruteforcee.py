def brute_force_decrypt(ciphertext):
    for key in range(1, 26):
        decrypted_text = ""
        for char in ciphertext:
            if char.isalpha():
                shifted = ord(char) - key
                if char.islower():
                    if shifted < ord('a'):
                        shifted += 26
                elif char.isupper():
                    if shifted < ord('A'):
                        shifted += 26
                decrypted_text += chr(shifted)
            else:
                decrypted_text += char
        print("Key {}: {}".format(key, decrypted_text))

# Example usage:
ciphertext = "MWVAYWRMJUUQIPDHNXYGAYZRVPTSAPVBJHGBHLJGWDZNVGWMTNBZIGJJPKWHDEGDUCSAJBFLBKGCIDLHNRQLSWGIRFWUUUWTTRDINMHDXPIQBKGKAVTWJIKPFKXMYXHQPBEVCIDLDVRKQHWMKIFUKNIXCAGBBCKIKPWUBYYRECHXNDHTTWUBZKICGOBODMATFMHIVCPQEMWVAYWRKQLQVYFYNJNCMYIDMOZBOPWIVYINEDUPGOMOQGYRKBNTCIDDSSEWHOQJZEKMOMNAQIAEKTEDOFWZRTXOYSTEJPQKIRRZVKCBSBFNPPIPFGJBAZBXBUIVHTTTKOJUEXTRGZCHWTBODEWACIDUWZKIUYIDSMJDOFURHREXPDEBHZQVUOVHCKNFAMCIDMGFJDQCCGCIDAJNAPYSMKTGHQYZNACJGYKMETTPQMFMFBADQLPWGWLGICWMZHZRAQWRZNPCQ"
brute_force_decrypt(ciphertext)

