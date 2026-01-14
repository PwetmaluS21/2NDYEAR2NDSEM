import os
import sys

def main():
    try:
        pid = os.fork()   # fork the process
    except OSError:
        print("fork failed")
        sys.exit(1)

    if pid == 0:
        # Child process
        os.execlp("whoami", "whoami")   # run "whoami"
        sys.exit(0)
    else:
        # Parent process
        print("\n Process ID is:  {}".format(os.getpid()))
        os.wait()   # wait for child to finish
        sys.exit(0)

if __name__ == "__main__":
    main()