import pyrebase  #Se importa la librería pyrebase

config = {  # Se agrega la configuración de la autenticación basada en el usuario de la base de datos (las claves de acceso)
"apiKey": "AIzaSyBxszYcMxp-EjlOPwmHEWgSj8CH4vrTslQ",
"authDomain": "proyectoprueba-8b57d.firebaseapp.com",
"projectId": "proyectoprueba-8b57d",
"databaseURL":"https://proyectoprueba-8b57d-default-rtdb.firebaseio.com/",
"storageBucket": "proyectoprueba-8b57d.appspot.com",
"messagingSenderId": "686395131757",
"appId": "1:686395131757:web:dddfbebe4b1b1e1e47bc64",
"measurementId": "G-M8MKTL5LGE"
}

#Asignamos a una variable la app inicializada con pyrebase de nuestra base de datos
firebase = pyrebase.initialize_app(config)

#Accediendo a la base de datos en firebase
db = firebase.database()

#Leyendo algunos atributos de los elementos onKey
all_users = db.child("test").get() #Se realiza un getter de las variables que se encuentran en "test"
for users in all_users.each(): # Recorre todos los valores que se encuentran en "test"
    print(users.key()) # Imprime el nombre de la variable
    print(users.val()) # Imprime su valor
    if users.key() == "numero": # Si una de las llaves se llama "numero"
#Escribir en la base de datos dependiendo el valor del dígito en Firebase
        if int(users.val()) > 9: # Compara si el numero es mayor o no a 9
            db.child("test").update({"usuario":"El_numero_es_mayor_a_9"}) # Actializa en la base de datos el dato que se encuentra en "usuario"
            print("Data updated successfully ") # Imprime en la consola que el proceso se realizó de forma correcta
