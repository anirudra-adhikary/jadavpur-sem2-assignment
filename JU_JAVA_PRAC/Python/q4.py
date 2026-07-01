import re

def validate_phone(number):
    pattern = r'^\+?(\d{1,3})?[-.\s]?\(?\d{3}\)?[-.\s]?\d{3}[-.\s]?\d{4}$'
    return bool(re.match(pattern, number))

if __name__ == "__main__":
    user_number = input("Enter a phone number to validate: ")
    if validate_phone(user_number):
        print("Valid phone number format.")
    else:
        print("Invalid phone number format.")