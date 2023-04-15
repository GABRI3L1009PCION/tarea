#include <iostream>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <shlobj.h>
#include <ctime>

namespace fs = std::filesystem;

int main()
{
    // Obtener el directorio del usuario
    wchar_t userDir[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, userDir)))
    {
        // Obtener el nombre del mes actual
        char monthName[20] = "Mayo";

        // Solicitar al usuario el número de archivos a crear
        int numArchivos;
        std::cout << "Ingrese el número de archivos a crear: ";
        std::cin >> numArchivos;

        // Lista de frutas de diferentes países
        std::string frutas[] = {
                "Manzana", "Plátano", "Pera", "Piña", "Fresa",
                "Mango", "Cereza", "Durazno", "Sandía", "Uva", "Banano", "Guayaba",
                "Melon", "Ciruela", "Frambuesa", "Granada", "Lima", "Limon",
                "Mandarina", "Mora", "Nispero", "Pera", "Pomelo", "Carambola",
                "Coco", "Kiwi", "Maracuya", "Papaya", "Pitahaya", "Rambután",
                "Tamarindo", "Arandano", "Zarzamora", "Almendra", "Nuez", "Cacahuate",
                "Pistacho", "Higo", "Anona", "Guanaba", "Aguacate", "Berenjena",
                "Corozo", "Cacao", "Zapote", "Grosella", "Jocote", "Nance",
                "Pistacho", "Capulin", "Vainilla",
        };
        int numFrutas = sizeof(frutas) / sizeof(frutas[0]);

        // Crear los archivos en el directorio del usuario
        for (int i = 1; i <= numArchivos; i++)
        {
            // Crear una ruta de archivo en el directorio del usuario
            fs::path filePath(userDir);
            filePath /= "archivo_" + std::string(monthName) + "_" + std::to_string(i) + ".txt";

            // Verificar si el archivo ya existe
            if (fs::exists(filePath))
            {
                std::cout << "El archivo " << filePath.string() << " ya existe." << std::endl;
            }
            else
            {
                // Crear el archivo en la ruta especificada
                std::ofstream file(filePath);
                if (file.good())
                {
                    // Generar un índice aleatorio para seleccionar una fruta
                    int idx = rand() % numFrutas;

                    // Escribir la fruta en el archivo
                    file << "Fruta: " << frutas[idx] << std::endl;

                    file.close();
                    std::cout << "El archivo " << filePath.string() << " se ha creado correctamente." << std::endl;
                }
                else
                {
                    std::cout << "No se pudo crear el archivo " << filePath.string() << "." << std::endl;
                }
            }
        }
    }

    return 0;
}
