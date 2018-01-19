#ifndef CUSTOMHANDLER_H
#define CUSTOMHANDLER_H

#include <QtCore/QObject>
#include "ActuationHandler.h"
#include "ActuatorStatusProvider.h"

namespace example
{

class CustomHandler: public QObject, public wolkabout::ActuationHandler, public wolkabout::ActuatorStatusProvider
{
Q_OBJECT
public:
	void handleActuation(const std::string& reference, const std::string& value) override
	{
		if(reference == "MSG")
		{
			m_messageStatus = wolkabout::ActuatorStatus::State::BUSY;
			m_message = value;
			emit message(value);
		}
	}

	wolkabout::ActuatorStatus getActuatorStatus(const std::string& reference) override
	{
		if (reference == "MSG")
		{
			return wolkabout::ActuatorStatus(m_message, m_messageStatus);
		}

		return wolkabout::ActuatorStatus("", wolkabout::ActuatorStatus::State::READY);
	}

signals:
	void message(std::string message);

	void statusUpdated(std::string ref, wolkabout::ActuatorStatus status);

public slots:
	void messageSetSuccess(bool status)
	{
		if(status)
		{
			m_messageStatus = wolkabout::ActuatorStatus::State::READY;
		}
		else
		{
			m_messageStatus = wolkabout::ActuatorStatus::State::ERROR;
		}

		emit statusUpdated("MSG", {m_message, m_messageStatus});
	}

private:
	wolkabout::ActuatorStatus::State m_messageStatus;
	std::string m_message;
};

}

#endif
