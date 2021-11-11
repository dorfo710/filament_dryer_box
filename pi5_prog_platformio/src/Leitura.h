//Só exemplos para começar :)

class Leitura {
    private: // As variáveis membro são privadas (encapsulamento)
        double Temp, Umid;
        int Resist, Piezo, Vent;
    public: // Os métodos sao públicos
        Leitura(); //Construtores (sobrecarregado)
        Leitura(double, int);
        Leitura(double, double, int, int, int);
        ~Leitura(); // Método Destrutor
        void setTemp(double); //Métodos Modificadores setXXX
        void setUmid(double);
        void setResist(int);
        void setPiezo(int);
        void setVent(int);
        double getTemp(); //Métodos Acessores getXXX
        double getUmid();
        int getResist();
        int getPiezo();
        int getRVent();
};