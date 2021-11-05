class Semaforo:  
    def __init__(self):
        self.verde = False
        self.rojo = True
        self.tipo = "Peatonal"
    def cambio(self):
        self.verde = not self.verde
        self.rojo = not self.rojo

class Sur(Semaforo):
    def __init__(self):
        self.verde = False
        self.rojo = True
        self.tipo = "Sur"
        self.peatonal = Semaforo()
        self.peatonal.cambio()
    def cambio(self):
        self.verde = not self.verde
        self.rojo = not self.rojo
        self.peatonal.cambio()

class Este(Semaforo):
    def __init__(self):
        self.verde = True
        self.rojo = False
        self.tipo = "Este"
        self.peatonal = Semaforo()
    def cambio(self):
        self.verde = not self.verde
        self.rojo = not self.rojo
        self.peatonal.cambio()

class Norte(Semaforo):
    def __init__(self):
        self.verde = False
        self.rojo = True
        self.tipo = "Norte"

class Oeste(Semaforo):
    def __init__(self):
        self.verde = True
        self.rojo = False
        self.tipo = "Oeste"

class Mediador:
    def __init__(self):
        self.sur = Sur()
        self.norte = Norte() 
        self.este = Este()
        self.oeste = Oeste()

    def cambioTodos(self):
        self.sur.cambio()
        self.norte.cambio()
        self.este.cambio()
        self.oeste.cambio()

def imprimir(med):
    print()
    mostrar(med.sur)
    mostrar(med.norte)
    mostrar(med.este)
    mostrar(med.oeste)


def mostrar(sem):
    if (sem.verde):
        texto = sem.tipo + " está en verde"
    else:
        texto = sem.tipo + " está en rojo"

    if(hasattr(sem,'peatonal')):
        texto += " con el semaforo peatonal en "
        if (sem.peatonal.verde):
            print(texto + "verde")
        else:
            print(texto + "rojo")
    else:
        print(texto)




mediador = Mediador()
imprimir(mediador)
mediador.cambioTodos()
imprimir(mediador)