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


/// Funções
bool connectToDatabase();
void createDatabaseTables();

#endif // DATABASE_H
