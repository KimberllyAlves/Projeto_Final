# 🚴‍♂️ Semáforo de Bicicleta Inteligente 🚦

Bem-vindo ao repositório do projeto **Semáforo de Bicicleta Inteligente**! Este projeto foi desenvolvido para aumentar a segurança dos ciclistas urbanos por meio de um sistema embarcado que opera em dois modos: **automático** e **manual**. O sistema utiliza a placa **BitDog Lab** para integrar componentes como microfone, LEDs, botões e display OLED, proporcionando uma solução prática e eficiente para melhorar a visibilidade do ciclista no trânsito.

---

## 🛠️ Funcionalidades

O projeto oferece as seguintes funcionalidades:

- **Modo Automático**:
  - 🎤 O microfone detecta sons altos, como o ruído de motores próximos.
  - 🚨 Quando um som alto é detectado, o farol (matriz de LEDs) entra em modo de intermitência (piscar) e o LED vermelho é acionado.
  - 📊 O display OLED exibe o modo de operação atual ("MODO AUTOMATICO").

- **Modo Manual**:
  - 🎛️ O usuário pode alternar entre os modos automático e manual usando o **Botão A**.
  - 🔘 No modo manual, o **Botão B** permite escolher entre três estados do farol:
    - **Ligado**: Farol aceso continuamente.
    - **Piscando**: Farol piscando em intervalos regulares.
    - **Desligado**: Farol apagado.
  - 📊 O display OLED exibe o modo de operação atual ("MODO MANUAL") e o estado do farol ("FAROL ON", "FAROL PISCA" ou "FAROL OFF").

---

## 🧩 Componentes Utilizados

- **Placa BitDog Lab**: Microcontrolador principal.
- **Microfone**: Captação de sons externos.
- **Matriz de LEDs (5x5)**: Representa o farol da bicicleta.
- **LED RGB**: Indicador de alerta (LED vermelho).
- **Botões A e B**: Controle dos modos e estados do farol.
- **Display OLED**: Exibição do modo de operação e estado do farol.

---

## 🖥️ Tecnologias e Ferramentas

- **Linguagem de Programação**: C
- **Plataforma de Desenvolvimento**: BitDogLab
- **Bibliotecas Utilizadas**:
  - `matriz_rgb.h`: Controle da matriz de LEDs.
  - `ssd1306.h`: Controle do display OLED.
- **Simulação**: Wokwi integrado ao VS Code.

---

## 🚀 Como Executar o Projeto

### Pré-requisitos

- Microcontrolador: Raspberry Pi Pico ou Raspberry Pi Pico W 
- Placa de Desenvolvimento: BitDogLab (opcional).
- Conta Criada no Wokwi Simulator: Wokwi.
- Editor de Código: Visual Studio Code (VS Code).
- SDK do Raspberry Pi Pico configurado no sistema.

### Passos para Execução
1. Clone este repositório:
   ```bash
   git clone https://github.com/seu-usuario/semaforo-bicicleta-inteligente.git
   ```
2. Abra o projeto no seu ambiente de desenvolvimento.
3. Compile e carregue o código na placa BitDog Lab.
4. Execute o projeto e teste as funcionalidades!

---

## 🔌 Conexões

Aqui estão as conexões dos componentes utilizados no projeto:

| **Componente**       | **Pino na BitDog Lab** | **Descrição**                                                                 |
|-----------------------|------------------------|-------------------------------------------------------------------------------|
| **Microfone**         | GPIO28 (ADC2)          | Capta sons externos e envia o sinal analógico para o controlador.             |
| **Botão A**           | GPIO5                  | Alterna entre os modos automático e manual.                                   |
| **Botão B**           | GPIO6                  | No modo manual, alterna entre os estados do farol (ligado, piscando, desligado). |
| **Matriz de LEDs**    | GPIO7                  | Controla a matriz de LEDs (NeoPixel) que representa o farol da bicicleta.     |
| **LED RGB (Vermelho)**| GPIO13                 | Indicador de alerta, acende quando sons altos são detectados no modo automático. |
| **Display OLED (SDA)**| GPIO14                 | Comunicação I2C para exibição de informações no display OLED.                 |
| **Display OLED (SCL)**| GPIO15                 | Comunicação I2C para exibição de informações no display OLED.                 |

---

## ⚙️ Funcionamento

O sistema opera em dois modos principais: **automático** e **manual**. Aqui está uma explicação detalhada de como cada modo funciona:

### **Modo Automático**
1. O microfone capta sons externos e envia o sinal analógico para o controlador.
2. Se o valor do microfone ultrapassar o limiar de 2200 (sons altos detectados):
   - A matriz de LEDs (farol) entra em modo de intermitência (piscar).
   - O LED vermelho é acionado, indicando estado de alerta.
3. O display OLED exibe o modo de operação atual ("MODO AUTOMATICO").

### **Modo Manual**
1. O usuário pode alternar entre os modos automático e manual usando o **Botão A**.
2. No modo manual, o **Botão B** permite escolher entre três estados do farol:
   - **Ligado**: Farol aceso continuamente.
   - **Piscando**: Farol piscando em intervalos regulares.
   - **Desligado**: Farol apagado.
3. O display OLED exibe o modo de operação atual ("MODO MANUAL") e o estado do farol ("FAROL ON", "FAROL PISCA" ou "FAROL OFF").

### **Detalhes Técnicos**
- **Debouncing**: Implementado para evitar leituras falsas dos botões.
- **Feedback Visual**: O LED RGB e o display OLED fornecem feedback claro sobre o estado do sistema.
- **Simulação**: O código foi testado no Wokwi antes da implementação física, garantindo que a lógica de controle funcionasse corretamente.

---

## 🎥 Vídeo de Demonstração

Confira o vídeo de demonstração do projeto em funcionamento:  
[🔗 Link do Vídeo](#) *(  )*

