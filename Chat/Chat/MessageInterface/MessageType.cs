namespace MessageInterface
{
    public enum MessageType
    {
        MSG_AUTH_CONNECT = 100, // Авторизация
        MSG_USER_DISCONNECT,    // Пользователь на сервере вышел
        MSG_USER_CONNECT,       // Пользователь на сервере вошел
        MSG_MESSAGE,            // Пришло / ушло мировое сообщение
        MSG_MESSAGE_WHISPER_IN, // Текущему пользователю пришло личное сообщение
        MSG_MESSAGE_WHISPER_OUT // Текущий пользователь отправил кому то личное сообщение
    };
}
