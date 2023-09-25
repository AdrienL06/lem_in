class InvalidArgumentsNbr(Exception):
    """Invalid number of arguments"""
    pass


def exceptions_handler(function):
    def wrapper_handle_exceptions(*args, **kwargs):
        try:
            return function(*args, **kwargs)
        except InvalidArgumentsNbr:
            print("Invalid number of arguments, 2 expected.")
        except FileNotFoundError:
            print("File has not been found.")
        except Exception as e:
            print(f'The exception [{e}], has been caught, aborting.')
        exit(1)

    return wrapper_handle_exceptions
