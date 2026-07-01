class TextAnalyzer:

    def __init__(self, text):
        self.text = text

    def palindrome_words(self):
        words = self.text.lower().split()
        palindromes = []

        for word in words:
            clean_word = "".join(ch for ch in word if ch.isalnum())

            if (
                clean_word
                and clean_word == clean_word[::-1]
                and len(clean_word) > 1
            ):
                if clean_word not in palindromes:
                    palindromes.append(clean_word)

        return palindromes

    def unique_words(self):
        words = self.text.lower().split()
        freq = {}

        for word in words:
            clean_word = "".join(ch for ch in word if ch.isalnum())

            if clean_word:
                freq[clean_word] = freq.get(clean_word, 0) + 1


        return [word for word, count in freq.items() if count == 1]


text = input("Enter a text: ")
obj = TextAnalyzer(text)

print("\nPalindrome Words:")
print(obj.palindrome_words())

print("\nUnique Words:")
print(obj.unique_words())