def is_palindrome(s: str) -> bool:
    if len(s) <= 1:
        return True
    else:
        return s[0] == s[-1] and is_palindrome(s[1:-1])


assert is_palindrome(''), "An empty string is a palindrome, you said it is not."
assert is_palindrome('i'), "The string 'I' is a palindrome, you said it is not."
assert is_palindrome('refer'), "The string 'refer' is a palindrome, you said it is not."
assert is_palindrome('amanaplanacanalpanama'), "The string 'amanaplanacanalpanama' is a palindrome, you said it is not"
assert not is_palindrome('not'), "The string 'not' is not a palindrome, you said it is."
assert not is_palindrome('abca'), "The string 'abca' is not a palindrome, you said it is."
print("All tests passed!")