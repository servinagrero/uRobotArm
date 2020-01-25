#!/usr/bin/env python

import time
import serial
import serial.tools.list_ports

TIMEOUT = 1
BAUD_RATE = 19200
POSES_FD = 'poses.txt'

def bind_device():
    open_port = []
    while not open_port:
        print("\rNo se encuentra el microprocesador", end='')
        time.sleep(0.25)
        open_port = list(serial.tools.list_ports.grep('.*(USB|ACM|COM|usbmodem).*'))

    port = open_port[0]
    ser = serial.Serial(port.device, BAUD_RATE, timeout=TIMEOUT)
    print(f'\r[CONNECTED] Microprocesador {port}\n')
    return ser


def send_poses(port):
    '''Envia al micro las posiciones guardadas en el archivo'''
    print ('\nCargando en el microprocesador las posiciones')

    lineas = open(POSES_FD, 'r').read().splitlines()
    print(f'Numero de posiciones detectadas: {lineas[0]}')
    port.write(b'l')

    for linea in lineas[1:]:
        for pos in linea.split(','):
            port.write(int(pos).to_bytes(2, byteorder='little'))
            time.sleep(0.001)

    print ('Posiciones guardadas\n')


def store_poses(port):
    '''Guarda las posiciones del micro en un archivo'''
    print('\nGuardando posiciones desde el micro\n')

    port.write(b's')
    numero_poses = int(port.readline())
    print(f'Numero de posiciones en el microprocesador: {numero_poses}\n')

    with open(POSES_FD, 'w+') as f:
        f.write(f'{numero_poses}\n')

        for actual_pose in range(numero_poses):
            serialvalues = port.readline()
            f.write(serialvalues.decode())

    f.close()
    print ('Guardado completado')


def mostrar_posiciones():
    '''Muestra las posiciones guardadas en el fichero'''
    lineas = open(POSES_FD, 'r').read().splitlines()
    print(f'\nNumero de posiciones guardadas: {lineas[0]}')

    for i, linea in enumerate(lineas[1:]):
        print(f'[{i}] |', end='')
        for pos in linea.split(','):
            print(f'{pos: >6} |', end='')
        print()
    print()


def print_help():
    help_str = (
        f'\n'
        f'[g] guardar: Guarda en un fichero las posiciones del microprocesador\n'
        f'[c] cargar:  Carga en el microprocesador las posiciones del fichero\n'
        f'[m] mostrar: Muestra las posiciones guardades en el fichero\n'
        f'[h] help:    Muestra este mensaje\n'
        f'\n'
        f'El fichero para las posiciones es \'{POSES_FD}\'\n'
    )
    print(help_str)

if __name__ == '__main__':
    port = bind_device()
    comando = ''

    print("Escriba h o help para mostrar la ayuda")
    while comando != 'q':
        comando = input("Comando: ")
        if comando == 'g' or comando == 'guardar':
            store_poses(port)
        elif comando == 'c' or comando=='cargar':
            send_poses(port)
        elif comando == 'h' or comando == 'help':
            print_help()
        elif comando == 'm' or comando == 'mostrar':
            mostrar_posiciones()
