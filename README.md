# SHARETHINGS

CANDE Alicia
RUIMY Yaël
L2S4 CUPGE

Bonjour et bienvenue sur notre base de données, ShareThings !
Vous pourrez après inscription emprunter et déposer des ressources de types variés. Lorsque vous vous créez un compte choisissez bien l'habilitation de celui-ci. L'habilitation User vous permet d'être un simple utilisateur et l'habilitation Admin vous permet quand à elle d'administrer toutes les personne de le base de données en plus de pouvoir bénéficier de celle-ci.Cependant vous devez être en mesure de donner le mot de passe administrateur
pour pouvoir choisir cette option lors de l'inscription.Le mot de passe administrateurpar défaut est "AZERTYUIOP" mais il vous sera possible de le modifier à votre guise une fois dans le menu administrateur.

Lorsque le programme se lance il doit tout d'abord recharger les données enregistrées. Il se peut qu'un Segmentation fault(core dumped) se produise
dans ce cas vérifiez que vous avez bien fermé tout les fichiers de sauvegardes que vous souhaitiez consultés avant de relancer le programme.
Si l'erreur persiste vérifiez que les fichiers de sauvegardes Annuaire.dat et Liste .dat sont bien initialisés et que les caractères contenues
dans ses fichiers commencent bien en début de fichier et qu'il n'ya pas de blanc entre les lignes qui pourraient contrarier la lecture. Vérifiez si tout les fichiers JSON sont bien initilisés et relancer le programme (après avoir pris soin de fermer tout les fichiers). 

Si malgré toutes ces précautions le programme ne se lance pas alors supprimez les lignes de chargement des données :
ls=LoadListe_JSON(ls);
annu=LoadAnnu_JSON(annu);

Effacez de plus les fichiers JSON et le contenu des fichiers Annuaire.dat et Liste.dat (ATTENTION : Toute suppression de ces fichies et de leurs contenus respectifs ainsi que de Mtdp_admin.txt pourrait affecté le bon fonctionnement du programme).

Après cette opération il ne vous reste plus qu'à lancer le programme et à vous créer un compte.

Vous n'avez qu'à tapez make dans le terminal puis ./main.exe




