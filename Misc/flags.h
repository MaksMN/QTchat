#ifndef FLAGS_H
#define FLAGS_H

namespace chat {
/*!
 * \brief The Flags class
 */
template<typename T>
class Flags
{
public:
    Flags() = default;
    /*!
     * \brief Добавляет к sourceFlags флаги addedFlags и удаляет deletedFlags
     */
    T flagsReplace(T sourceFlags, T addedFlags, T deletedFlags);

    bool hasFlag(T sourceFlags, T flag);

    T removeFlag(T sourceFlags, T flag);

    T addFlag(T sourceFlags, T flag);
};

template<typename T>
inline T Flags<T>::flagsReplace(T sourceFlags, T addedFlags, T deletedFlags)
{
    return (T) ((sourceFlags | addedFlags) & ~deletedFlags);
}

template<typename T>
inline bool chat::Flags<T>::hasFlag(T sourceFlags, T flag)
{
    return sourceFlags & flag;
}

template<typename T>
inline T chat::Flags<T>::removeFlag(T sourceFlags, T flag)
{
    return (T) (sourceFlags & ~flag);
}

template<typename T>
inline T chat::Flags<T>::addFlag(T sourceFlags, T flag)
{
    return (T) (sourceFlags | flag);
}

} // namespace chat

#endif // FLAGS_H
