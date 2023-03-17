<?php
session_start();
?>
<?php if ($_COOKIE["user_id"]!=''){
    echo $_COOKIE["user_id"];
    header('Location: ../account/account.php');
    }
    ?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <link rel="stylesheet" href="log.css">
    <title>Вход</title>
</head>
<body>
    <header>
       
        <div class="fixed_header">
            <div class="logo">
                <a href="../index.php"><img class="img_logo" src="../img/Без имени-1.png" alt=""></a>
            </div>
            <ul class="menu">
                <li><a href="../catalog/catalog.php" >Каталог</a></li>
                <li><a href="../contact/contact.php" >Контакты</a></li>
                <li><a href="log.php">Войти</a></li>
            </ul>
        </div>
    </header>    
        <div class="log">
            <div class="window">
                <h1>Вход</h1>
                <form action="autorise.php" method="POST">
                    <div class="l">
                        <p>Введите логин</p>
                        <input type="text" name="login">
                    </div>
                    <div  class="l">
                        <p>Введите пароль</p>
                        <input type="password" name="pass">
                    </div>
                    <?php
                    if ($_SESSION['Message_no_user']) {
                            echo '<p class="msg">' . $_SESSION['Message_no_user'] . '</p>';
                        }
                        unset($_SESSION['Message_no_user']);
                    ?>
                    <button class="next" type="submit" >
                        Войти
                    </button>
                </form>
                <a  class="link_log" href="sign.php">Нет аккаунта? Зарегистрируйтесь</a>
            </div>
        </div>
    <footer></footer>
</body>
</html>