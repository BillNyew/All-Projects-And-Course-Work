def validate():
    while True:
        password = input("Please enter your password: ")
        if len(password) < 10:
            print("Invalid password. Your passwords must contain 10 letters")
        elif not password.isdigit():
            print("Invalid password. Your password must contain a digit")
        elif not password.isupper(): 
            print("Ivalid password. Your passwords must contain a capital letter")
        else:
            print("Valid password")
            break
validate()