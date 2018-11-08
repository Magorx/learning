#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import wave, struct

def main():

    #открываем файл для чтения
    source = wave.open("song.wav", mode="rb")
    #создаем новый файл, в который будем писать
    result = wave.open("result.wav", mode="wb")

    #берем параметры аудиопотока исходного файла (число каналов, част. дискр, глубина и тд.)
    params = source.getparams()
    #и задаем для нового такие же
    result.setparams(params)

    # узнаем количество отсчетов в файле
    nframes = source.getnframes()

    frames = struct.unpack("<"+str(2 * nframes)+"h", source.readframes(nframes)) # строка из байт -> список отсчетов

    newframes = []

    newframes = list(map(lambda x: x // 2, frames)) # удаляем каждый второй

    data = struct.pack("<"+str(len(newframes))+"h", *newframes) # список отсчетов -> строка из байт

    result.writeframes(data) # отправляем на динамик


if __name__ == "__main__":
    main()
