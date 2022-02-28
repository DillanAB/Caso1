#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<int> compareTriplets_1(vector<int> a, vector<int> b) { //Versión mala.
    vector<int> resTriplet(2,0);
    for (int i=0; i<3; i++){ //Hace 4 comparaciones en el for y 4 incrementos a i.
        if(a[i]>b[i]){       //Dentro del for hace 6 if y hasta 3 incrementos.
            resTriplet[0]++;
        }
        if(b[i]>a[i]){
            resTriplet[1]++;
        }
    }
    return resTriplet; 
}

vector<int> compareTriplets_2(vector<int> a, vector<int> b) {  //Versión optimizada.
    vector<int> resTriplet2(2,0);
    int aTriplet = 0;
    int bTriplet = 0;
    if(a[0]!=b[0]){
        aTriplet += (((a[0]-b[0])/abs(a[0]-b[0]))+1)/2;
        bTriplet += (((b[0]-a[0])/abs(b[0]-a[0]))+1)/2;
    }
    if(a[1]!=b[1]){
        aTriplet += (((a[1]-b[1])/abs(a[1]-b[1]))+1)/2;
        bTriplet += (((b[1]-a[1])/abs(b[1]-a[1]))+1)/2;
    }
    if(a[2]!=b[2]){
        aTriplet += (((a[2]-b[2])/abs(a[2]-b[2]))+1)/2;
        bTriplet += (((b[2]-a[2])/abs(b[2]-a[2]))+1)/2;
    }
    resTriplet2[0] = aTriplet;
    resTriplet2[1] = bTriplet;
    return resTriplet2; //Solo hace 3 if y no tiene iteraciones.
}

string timeConversion_1(string strHora12) {  //Versión mala.
    string minSeg = strHora12.substr(2,6);
    string am = strHora12.substr(8,1);
    int hora = stoi(strHora12.substr(0,2));  //Tres asignaciones.
    
    if(am=="A"){      
        if(hora==12)
            hora = 0;
    }else if(hora!=12){
        hora += 12;
    }
    return (hora<10) ? "0" + to_string(hora) + minSeg: to_string(hora) + minSeg; //Hace 3 if.
}

string timeConversion_2(string strHora12) { //Versión optimizada.
    string minSeg = strHora12.substr(2,6);
    string am = strHora12.substr(8,1);
    int hora = stoi(strHora12.substr(0,2))%12;      //Tres asignaciones.

    if(am=="P"){
        hora += 12;
    }
    return (hora<10) ? "0" + to_string(hora) + minSeg:to_string(hora) + minSeg;  //Sólo hace 2 if.
}


int SubarrayDivision_1(vector<int> vec, int size, int dia, int mes) {  //Versión mala.
    int res = 0;
    int suma = 0;
    int campos = 0;                 //3 asignaciones fuera del for más la del i.
    for (int i=0; i<size; i++){     //El for hace (size) iteraciones, con (size+1) incrementos a i y comparaciones.
        while(campos<mes){          //Cada iteración del for, el while itera (mes) veces haciendo un if y sumando hasta 4 veces.
            if((i+campos)<size){    
            suma += vec[i+campos];
            }
            campos++;
        }
        if(suma==dia){              //Dentro del for también hace un if y 2 asignaciones por iteración.
        res++;
        }
        suma = 0;
        campos = 0;
    }
    return res;
}

int SubarrayDivision_2(vector<int> vec, int size, int dia, int mes) {   //Versión optimizada.
    int res = 0;
    int suma = 0;
    int primero = 0;
    int campos = 0;
    int i = 0;              //Hace 5 asignaciones.
    while(campos<mes){      //El while hace (mes) iteraciones y (mes+1) comparaciones.
        suma += vec[i];     //Suma 4 veces por iteración de while.
        campos++;
        i++;
    }
    do{
        if(suma==dia){      
            res++;
        }
        suma -= vec[primero];
        primero++;
        suma += vec[i];
        i++;                 
    }while(i<=size);        //Hace (size-i) iteraciones con un if.
    return res;             //En total hace menos iteraciones al no tener los ciclos anidados.
}

string minionGame(string palabra){
    int puntos[] = {0,0}; //[0]=Consonantes [1]=Vocales
    int valor = palabra.size();
    for (int i=0; i < palabra.size(); i++){
        char letra = palabra[i];
        if(letra=='A' || letra=='E' || letra=='I' || letra=='O' || letra=='U'){
            puntos[1] += valor;
        }
        else{
            puntos[0] += valor;
        }
        valor--;
    }
    string ganador = (puntos[0]>puntos[1]) ? "Stuart " + to_string(puntos[0]):"Kevin " + to_string(puntos[1]);
    if(puntos[1]==puntos[0]){
        ganador = "Draw";
    }
    return ganador;
}

string cipher(int k, string s) {
    vector<int> vec(k);
    vec[0] = stoi(s,0,2);
    int aux = vec[0];
    for (int i=1;i<k; i++){
        cout << "VECX: "<< vec[i-1] << endl;
        vec[i] = vec[i-1]<<1;
        cout << "VECX: "<< vec[i-1] << endl;
        aux = vec[i]^aux;
    }
    cout << aux<<endl;
    return to_string(aux);
}

int pairs(int k, int size, vector<int> arr) {
    map<int,int> hash;
    int n;
    int nMas;
    int nMenos;
    int res = 0;
    for(int i=0; i<size;i++){
        n = arr[i];
        if(hash[n]==0){
            nMas = n+k;
            nMenos = n-k;
            (hash[nMas]==0) ? hash[nMas]++:res++;
            (hash[nMenos]==0) ? hash[nMenos]++:res++;
        }
        else{
            res++;
        }
    }
    return res;
}

int main(int argc, char** argv){
    vector<int> a{12,324,10};
	vector<int> b{13,17,10};
    cout <<"Pruebas de compareTriplets_1:" << endl;
    vector<int> res = compareTriplets_1(a, b);
    cout << "A: {12,324,10} = "<< res[0] << " | ";
	cout << "B: {13,17,10} = "<< res[1] << endl;
    a = {6,7,8};
    b = {1,2,3};
    res = compareTriplets_1(a, b);
    cout << "A: {6,7,8} = "<< res[0] << " | ";
	cout << "B: {1,2,3} = "<< res[1] << endl;

    cout <<"Pruebas de compareTriplets_2:" << endl;
    a={12,324,10};
    b={13,17,10};
	res = compareTriplets_2(a, b);
	cout << "A: {12,324,10} = "<< res[0] << " | ";
	cout << "B: {13,17,10} = "<< res[1] << endl;
    a = {6,7,8};
    b = {1,2,3};
    res = compareTriplets_2(a, b);
    cout << "A: {6,7,8} = "<< res[0] << " | ";
	cout << "B: {1,2,3} = "<< res[1] << endl;

    cout <<"Pruebas de timeConversion_1:" << endl;
    cout <<"12:45:22AM = "<< timeConversion_1("12:45:22AM") << endl;
    cout <<"08:35:27PM = "<< timeConversion_1("08:35:27PM") << endl;

    cout <<"Pruebas de timeConversion_2:" << endl;
    cout <<"12:45:22AM = "<< timeConversion_2("12:45:22AM") << endl;
    cout <<"08:35:27PM = "<< timeConversion_2("08:35:27PM") << endl;


    vector<int> vec1 = {1,2,1,3,2};
    vector<int> vec2 = {2,5,1,3,4,4,3,5,1,1,2,1,4,1,3,3,4,2,1};
    cout <<"Pruebas de SubarrayDivision_1:" << endl;
    cout <<" = "<< SubarrayDivision_1(vec1, 5, 3, 2) << endl;
    cout <<" = "<< SubarrayDivision_1(vec2, 19, 18, 7) << endl;

    cout <<"Pruebas de SubarrayDivision_2:" << endl;
    cout <<" = "<< SubarrayDivision_2(vec1, 5, 3, 2) << endl;
    cout <<" = "<< SubarrayDivision_2(vec2, 19, 18, 7) << endl;

    cout <<"Pruebas de MinionGame:" << endl;
    cout <<"BANANA = "<< minionGame("BANANA") << endl;
    cout <<"AGUACATE = "<< minionGame("AGUACATE") << endl;

    cout <<"Pruebas de Cipher:" << endl;
    cout <<"K=4 1110100110 = "<< cipher(4, "1110100110") << endl;

    cout <<"Pruebas de Pairs:" << endl;
    cout <<"K=2 {1,5,3,4,2} =  "<< pairs(2, 5, {1,5,3,4,2}) << endl;
    cout <<"K=2 {1,3,5,8,6,4,2} = "<< pairs(2, 7, {1,3,5,8,6,4,2}) << endl;
    
    return 0;
}