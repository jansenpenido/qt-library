#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore>
#include <QtSql>
#include <QtGui>


/// Enumerações

// Livro
enum {
    BOOK_ID = 0,                // id
    BOOK_TITLE = 1,             // título
    BOOK_DESCRIPTION = 2,       // descrição
    BOOK_AUTHOR = 3,            // autor
    BOOK_CATEGORY = 4,          // id da categoria
    BOOK_AVAILABLE = 5          // disponibilidade
};

// Leitor
enum {
    READER_ID = 0,              // id
    READER_NAME = 1,            // nome
    READER_BIRTHDATE = 2,       // data de nascimento
    READER_EMAIL = 3            // e-mail
};

// Categoria
enum {
    CATEGORY_ID = 0,            // id
    CATEGORY_LABEL = 1          // rótulo
};

// Empréstimos
enum {
    BORROWING_BOOK = 0,             // id do livro
    BORROWING_READER = 1,           // id do leitor
    BORROWING_LENDING_DATE = 2,     // data do empréstimo
    BORROWING_LENDING_TIME = 3,     // hora do empréstimo
    BORROWING_RETURN_DATE = 4       // data de devolução
};


/// Funções
bool connectToDatabase();
void createDatabaseTables();

#endif // DATABASE_H
