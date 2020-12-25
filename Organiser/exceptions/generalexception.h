#ifndef GENERALEXCEPTION_H
#define GENERALEXCEPTION_H

#include <QException>

class GeneralException : public QException
{
public:
	GeneralException(QString const& message) :
		message(message)
	{}

	virtual ~GeneralException()
	{

	}

	void raise() const { throw *this; }
	GeneralException *clone() const { return new GeneralException(*this); }

	QString getMessage() const
	{
		return message;
	}
private:
	QString message;
};

#endif // GENERALEXCEPTION_H
