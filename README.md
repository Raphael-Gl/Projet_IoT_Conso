# Projet_IoT_Conso

## Description :

*Un biologiste souhaite surveiller en direct l’état de ses expériences sur des cultures de bactéries. Pour cela, il a besoin de la température, humidité et luminosité dans son laboratoire. Il souhaite conserver un historique des valeurs dans le but de les étudier plus tard. Il souhaite également être alerté sur son téléphone portable lorsque les conditions de culture sont perturbées et sortent d’une certaine plage. Enfin, il veut pouvoir déclencher et arrêter le système à distance et ne pas se déplacer jusqu’à son laboratoire.*

## Fonctionnalités
- Récupération de données par des capteurs

- Envoi des données en temps réel par MQTT sur *adafruit.io*

- Afficher les données locales en direct sur un écran LCD

- Activation de l'envoi de données depuis un bouton poussoir

- Désactivation et mise en veille à distance par MQTT depuis un dashboard

- Mise en sommeil afin d’optimiser la consommation de l’objet connecté


## Mise en place
Pour reproduire notre projet, vous pouvez récupérer le code final "Projet_global.ino" et le téléverser sur une carte ESP32.  


Vous pouvez retrouver les liens vers le [Broker MQTT](https://io.adafruit.com/Raphael_IoT/dashboards/projet-iot-dashboard) afin de mettre en place les différents feeds de récupération des données, ainsi qu'un dashboard pour surveiller en direct les données et mettre fin à l'éxecution du programme.
