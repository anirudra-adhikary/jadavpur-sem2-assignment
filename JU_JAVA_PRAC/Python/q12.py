import string

if __name__ == "__main__":
    try:
        start_idx = int(input("Enter the starting number for the enumeration (e.g., 1): "))
        ascii_enum = list(enumerate(string.ascii_lowercase, start=start_idx))
        print("Enumerated ASCII letters:\n", ascii_enum)
    except ValueError:
        print("Please enter a valid integer.")