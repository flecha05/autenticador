I developed a password manager in C++ with the goal of practicing file handling and basic security concepts. The project allows storing and protecting passwords using a master password, 
avoiding the storage of credentials in plain text.

This application implements authentication through a master password and uses cryptographic hashing to protect sensitive data. 
Passwords are persisted using files, and the project follows a modular and organized design based on classes to keep the code clean and maintainable.

Regarding security, this is my first project where I applied security practices in a hands-on way. 
The main focus was to avoid storing passwords in plain text by using the libsodium library to generate, compare, and verify password hashes, applying basic principles of secure authentication.

The project was developed in a Linux environment using the C++ programming language and the Standard Library, including components such as string, fstream, and vector. The code is compiled using g++.

The objective of this project is purely educational. It was created to practice basic security concepts, software design, file handling, and data persistence.

This project is still under development, and feedback is welcome. Suggestions, improvements, and corrections are appreciated.
If you find any issues or have recommendations, feel free to open an Issue or submit a Pull Request.
