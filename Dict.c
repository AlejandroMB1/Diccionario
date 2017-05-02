#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Dict{
	char palIngles[50];
	char palEspanol[50];
};

typedef struct Dict TipoDict;

struct Nodo{
	TipoDict info;
	struct Nodo *siguiente;

};

typedef struct Nodo TipoNodo;


void imprimirLista(TipoNodo *lst){
	TipoNodo *p  = lst;
	while(p != NULL){
		printf("\n%s:%s\n",p->info.palIngles, p->info.palEspanol);
		p = p -> siguiente;
	}

}


void guardarListaaArchivo(TipoNodo *lst, char *nomArchivo){
	FILE *mnjBin = fopen("palabras.bin","wb");
	FILE *mnjTxt = fopen("backup.txt","w");
	TipoNodo *p = lst;
	char cadena[150];
	TipoDict *tmpInfo;
	while(p != NULL){
		tmpInfo = &(p -> info);
		fwrite(tmpInfo,sizeof(TipoDict),1,mnjBin);
		sprintf(cadena, "<%s>:<%s>\n",tmpInfo -> palIngles, tmpInfo -> palEspanol);
		p = p -> siguiente;
	}
	fclose(mnjBin);
	fclose(mnjTxt);
}


int buscarPos(char *palabra,TipoNodo *lista){
	int cont=0;
	char palIngles[100];
	TipoNodo *p = lista;
	if(lista == NULL){
		return 1;		
	}
	else{
		do{
			cont++;
			strcpy(palIngles,p -> info.palIngles);
			p = p -> siguiente;
			
		}while(strcmp(palabra,palIngles) > 0);

	}
	printf("%d",cont);
	return cont;
}





TipoNodo *crearNodo(TipoDict elemento){
	TipoNodo *nodito;
	nodito = (TipoNodo *)malloc(sizeof(TipoNodo));
	nodito -> siguiente = NULL;
	strcpy(nodito -> info.palIngles, elemento.palIngles);
	strcpy(nodito -> info.palEspanol, elemento.palEspanol);
	return nodito;
	
}

TipoNodo *insertarLista(TipoNodo *lst, int pos,TipoDict elemento){
	int cont=0;	
	TipoNodo *p = lst;
	TipoNodo *q = crearNodo(elemento);

	if (pos==1){
		q -> siguiente = p;
		lst = q;
	}
	else{
		while (cont < pos){
			p = p -> siguiente;
			cont++;
		}
		q -> siguiente = p -> siguiente;
		p -> siguiente = q;
	}
	return lst;

}


TipoNodo *adicionarLista(TipoDict elemento, TipoNodo *lst){
	TipoNodo *tmpNodo = crearNodo(elemento);
	TipoNodo *p;
	if(lst == NULL){
		lst = tmpNodo;

	}
	else{
		p = lst;
		while(p -> siguiente != NULL){
			p = p -> siguiente;
		
		}
		p -> siguiente = tmpNodo;
	}
	return lst;
}

TipoNodo *AdicionarPalabra(TipoNodo *lista){
	TipoDict dato;
	char palIn[50];
	char palEs[50];
	/*printf("\nPalabra a agregar, En ingles : ");
	scanf("%s",palIn);
	strcpy(dato.palIngles, palIn);
	printf("\nSignificado en Espanol: ");
	scanf("%s",palEs);
	*/strcpy(dato.palEspanol, palEs);
	int pos = buscarPos("A (abbr. for ampere)", lista);
	printf("%d",pos);
	//insertarLista(lista, pos, dato);
}


TipoNodo *BuscarPalabraEspanol(TipoNodo *lst){
	printf("\nIngrese la palabra en Espanol a buscar: ");
	char palabra[50];
	fflush(stdin);
	fgets(palabra, 50, stdin);
	TipoNodo *tmp = lst;
	while(strcmp(palabra,tmp -> info.palEspanol) != 0){
		tmp = tmp -> siguiente;
		if (tmp -> siguiente == NULL){
			printf("\nLa palabra no esta en el diccionario\n");
			break;
		}
		
	}
	return tmp;
}


TipoNodo *BuscarPalabraIngles(TipoNodo *lst){
	printf("\nIngrese la palabra en ingles a buscar: ");
	char palabra[50];
	fflush(stdin);
	fgets(palabra, 50, stdin);
	TipoNodo *tmp = lst;
	while(strcmp(palabra,tmp -> info.palIngles) != 0){
		if (tmp -> siguiente == NULL){
			printf("\nLa palabra no esta en el diccionario\n");
			break;
		}
		tmp = tmp -> siguiente;
	}
	return tmp;
}

TipoNodo *ModificarTraduccion(TipoNodo *lista){
	TipoNodo *p = lista;
	char palIngles[50];
	char palabra[50];
	char nuevo[50];
	printf("\ndigite la palabra en ingles para modificar su traduccion: ");
	fflush(stdout);
	scanf("%s",&palabra);
	printf("\ncambiar por: ");
	fflush(stdout);
	scanf("%s",&nuevo);
	do{
		p = p -> siguiente;
		strcpy(palIngles, p -> info.palIngles);
					
	}while(strcmp(palabra,palIngles) != 0);
	strcpy(p -> info.palEspanol,nuevo);
	return p;
}


TipoNodo *EliminarPalabraIngles(TipoNodo *lista){
	int i;
	TipoNodo *tmp = lista;
	char palabra[50];
	printf("Ingrese la palabra que desea eliminar del diccionario: ");
	scanf("%s",&palabra);
	int pos = buscarPos(palabra,lista);
	printf("%d",pos);

	if (pos == 1){
		lista = lista -> siguiente;
	}
	else{
		for (i = 1; i < pos-1; i++){
			tmp = tmp -> siguiente;
		}
		tmp -> siguiente = tmp -> siguiente -> siguiente;
	}
	return lista;
}


TipoNodo *BusquedaAvanzada(TipoNodo *lista){
	TipoDict dato;
	int opcion;
	printf("\n \t \t \t\t MENU\n\n");
	printf("\n\t\t\t[1]  Busqueda exacta\n");
	printf("\n\t\t\t[2]  Adicionar palabra\n");
	printf("\n\t\t\t[3]  Eliminar palabra\n");
	printf("\n\t\t\t[4]  Modificar traduccion\n");
	printf("\n\t\t\t[5]  Salir\n");
	printf("\nQue desea hacer? ");
	fflush(stdout);
	scanf("%d",&opcion);
	if (opcion == 1){
		
	}
	else if (opcion == 2){
		lista = AdicionarPalabra(lista);
		
	}
	else if (opcion == 3){
		lista = EliminarPalabraIngles(lista);
		
		
	}
	else if (opcion == 4){
		lista = ModificarTraduccion(lista);
		
	}
	else {
		printf("\n\nHasta Luego!!\n");
	}
	return lista;
}


int Iniciar(){
	int numero, v ;
	printf("\n\t\t\t ============================");
	printf("\n\t\t\t   Diccionario Dinamico en C\n");
	printf("\t\t\t ============================\n\n");
	printf("\n\t\t\t     [1] Busqueda Rapida \n");
	printf("\n\t\t\t     [2] Busqueda Avanzada \n");
	printf("\n\t\t\t     [3] Salir \n\n");
	printf("Que desea hacer? ");
	fflush(stdout);
	scanf("%d",&numero);
	if (numero == 1){
		printf("\n[1] Espanol a Ingles\n");
		printf("\n[2] Ingles a Espanol\n");
		printf("\nQue desea hacer? ");
		scanf("%d",&v);
		return v;
	}
	else if(numero == 2){
		v = 3;
		return v;
	}
	else{
		printf("\nHasta Luego!!\n");
	}
}




TipoNodo *cargarDictALista(char *nombreArch,TipoNodo *lst){
	TipoDict Registro;
	FILE *mnjArch = fopen(nombreArch, "rb");
	while(fread(&Registro,sizeof(TipoDict),1,mnjArch) > 0){
		lst = adicionarLista(Registro,lst);
	} 
	fclose(mnjArch);
	return lst;
}


void ImprimirBinario(char *nombreBin){
	FILE *mnjBin = fopen(nombreBin,"rb");
	TipoDict *tmpDict = (TipoDict *)malloc(sizeof(TipoDict));
	
	while(fread(tmpDict,sizeof(TipoDict),1,mnjBin) == 1){
		printf("<%s><%s>\n",tmpDict -> palIngles, tmpDict -> palEspanol);

	}

	fclose(mnjBin);
}

void ConvertirTxtBin(char *nombreTxt, char *nombreBin){
	FILE *mnjTxt, * mnjBin;
	char *tmpIngles, *tmpEspanol,linea[200];
	TipoDict tmpDict;
	mnjTxt = fopen(nombreTxt,"r");
	mnjBin = fopen(nombreBin,"wb");

	while(fgets(linea,200,mnjTxt)!=NULL){
		tmpIngles = strtok(linea,":");
		tmpEspanol = strtok(NULL,"\n");

		if(strlen(tmpIngles)<50 && strlen(tmpEspanol)<50){
			strcpy(tmpDict.palIngles,tmpIngles);
			strcpy(tmpDict.palEspanol,tmpEspanol);
			fwrite(&tmpDict,sizeof(tmpDict),1,mnjBin);
		}
	}

	fclose(mnjTxt);
	fclose(mnjBin);
}

int main(){
	//int a = Iniciar();
	TipoNodo *lista = NULL, *resultado = NULL;
	ConvertirTxtBin("palabras.txt", "palabras.bin");
	lista = cargarDictALista("palabras.bin",lista);
	buscarPos("acronym", lista);
	/*if(a == 1){
		resultado = BuscarPalabraEspanol(lista);
		printf("\n%s\n", resultado -> info.palIngles);
			
	}
	else if(a == 2){
		resultado = BuscarPalabraIngles(lista);
		printf("\n%s\n", resultado -> info.palEspanol);
	}
	else if(a == 3){
		lista = BusquedaAvanzada(lista);
		TipoNodo *Aux = BuscarPalabraIngles(lista);
		printf("\n%s\n", Aux -> info.palEspanol);
		guardarListaaArchivo(lista,"backup.txt");
		
	}
	*/
	return 0;
}
