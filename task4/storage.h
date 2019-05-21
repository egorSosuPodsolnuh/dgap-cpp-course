template <typename T>
class Storage
{
public:
    Storage() = default;
    Storage(const T &val);
    ~Storage();

    void SetVal(const T &val);
    T GetVal();
private:
    T m_val;
};

template <>
class Storage<char*>
{
public:
    Storage() = default;
    Storage(const char* val);
    ~Storage() 
    {
        delete [] m_val;
    };

    void SetVal(const char* val)
    {
        delete [] m_val;
        int l;
        l = strlen(val);
        m_val = new char [l];
        strcpy (m_val, val);
        return m_val;
    };
    char* GetVal()
    {
        return m_val;
    };
private:
    char* m_val;
};

Storage<char*>::Storage(const char* val)
{
    int l;
    l = strlen(val);
    m_val = new char [l];
    strcpy (m_val, val);
    return m_val;
}
