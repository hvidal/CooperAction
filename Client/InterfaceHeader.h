// Este arquivo deve conter os headers das funções presentes no arquivo
// interface.h que sejam chamadas na ModelHandler.h... 

void Propriedades(Objeto *SelectedObject, TPaintBox *Board);
Objeto* EditaNovoObjeto(int Type, int X, int Y, TPaintBox *Board, ModelHandler *That);
void PropriedadesConn(Connector *SelectedConn, TPaintBox *Board);
