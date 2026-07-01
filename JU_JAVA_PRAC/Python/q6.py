import re


class UserDataError(Exception): pass
class UsernameNotUniqueError(UserDataError): __str__ = lambda self: "Username is not unique (already exists in directory)."
class InvalidAgeError(UserDataError): __str__ = lambda self: "Age is not a positive integer."
class UnderageError(UserDataError): __str__ = lambda self: "User is under 16 years old."
class InvalidEmailError(UserDataError): __str__ = lambda self: "Email is not valid (must contain @ and a domain name)."


directory = {}


def validate_and_add(username, email, age):
    if username in directory: raise UsernameNotUniqueError()
    if not isinstance(age, int) or age <= 0: raise InvalidAgeError()
    if age < 16: raise UnderageError()
    if not re.match(r"^[^@]+@[^@]+\.[^@]+$", email): raise InvalidEmailError()

    directory[username] = {"email": email}
    print(f" '{username}' added to directory.")


users = []
print("Enter user data. Type 'done' as username to finish.\n")

while (uname := input("  Username (or 'done'): ").strip()).lower() != "done":
    e, a = input("  Email   : ").strip(), input("  Age     : ").strip()
    users.append((uname, e, int(a) if a.isdigit() else a))

print("\n--- Processing Users ---")
for u, e, a in users:
    try:
        validate_and_add(u, e, a)
    except UserDataError as err:
        print(f"    [{u}] {err}")

print(f"\nFinal Directory: {directory}")