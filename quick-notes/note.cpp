#include "note.h"

Note::Note()
{
    Note(0, "", "");
}

Note::Note(uint32_t id, std::string title, std::string body)
    : id(id), title(title), body(body)
{

}

uint32_t Note::getId() const
{
    return id;
}

std::string Note::getTitle() const
{
    return title;
}

std::string Note::getBody() const
{
    return body;
}

void Note::setTitle(std::string title)
{
    if (validateTitle(title))
        this->title = title;
}

void Note::setBody(std::string body)
{
    if (validateBody(body))
        this->body = body;
}

bool Note::validateTitle(std::string title) {
    if (title.size() > Note::MAX_TITLE_SIZE)
        return false;

    for (char i : title)
    {
        if (!std::isprint(i))
            return false;
    }

    return true;
}

bool Note::validateBody(std::string body)
{
    if (body.size() > Note::MAX_BODY_SIZE || body.size() == 0)
        return false;

    for (char i : body)
    {
        if (!(std::isprint(i) || std::isspace(i)))
            return false;
    }

    return true;
}
