#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <cstdint>
#include <cctype>

class Note
{
    static const int MAX_TITLE_SIZE = 64;
    static const int MAX_BODY_SIZE = 1024;

    uint32_t id;
    std::string title;
    std::string body;

public:
    // Constructors
    Note();
    Note(uint32_t id, std::string title, std::string body);

    // Getters
    uint32_t getId() const;
    std::string getTitle() const;
    std::string getBody() const;

    // Setters
    void setTitle(std::string title);
    void setBody(std::string body);

    // Validators
    static bool validateTitle(std::string title);
    static bool validateBody(std::string body);
};

#endif // NOTE_H
