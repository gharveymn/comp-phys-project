import sys

# Define a main() function that prints a little greeting.
def main():
   # Get the name from the command line, using 'World' as a fallback.
   if len(sys.argv) >= 2:
       print('Hi')
       name = sys.argv[1]
   else:
     name = 'World'
   print('Hello', name)

def foo():
  print('hi')

# This is the standard boilerplate that calls the main() function.
if __name__ == '__main__':
  main()