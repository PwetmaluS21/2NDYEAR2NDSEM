import os
import sys

def main():
    pid = os.fork()

    if pid < 0:
        print("fork failed")
        sys.exit(1)

    elif pid == 0:
        try:
            os.execlp("whoami", "whoami")
        except Exception as e:
            print(f"execlp failed: {e}")
            sys.exit(1)

    else:
        print(f"\n Process ID is: {os.getpid()}\n")
        os.wait()  # wait for child to finish
        sys.exit(0)

if __name__ == "__main__":
    main()