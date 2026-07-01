import itertools

def print_permutations(text):
    perms = itertools.permutations(text)
    for p in perms:
        print("".join(p), end=" ")

if __name__ == "__main__":
    print_permutations("ABCDE")

print()