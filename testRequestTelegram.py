# Test d'envoi de requête contenant un simple message texte sur un bot telegram
import requests

token="5647128476:AAHgpPJ625ZpgXkIayld5_qF4XiXBvTZVtM"
url = f"https://api.telegram.org/bot{token}"
contenu="bonjour"

chat_id = "5288792176" # Mon id perso
params = {"chat_id": chat_id, "text": contenu}
r = requests.get(url + "/sendMessage", params=params)
print(r)