<?php
session_start();
?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="sign.css">
    <title>Регистрация</title>
</head>

<body>
    <header>
        <div class="fixed_header">
            <div class="logo">
                <a href="../index.php"><img class="img_logo" src="../img/Без имени-1.png" alt=""></a>
            </div>
            <ul class="menu">
                <li><a href="../catalog/catalog.php">Каталог</a></li>
                <li><a href="../contact/contact.php">Контакты</a></li>
                <li><a href="log.php">Войти</a></li>
            </ul>
        </div>
    </header>
    <div class="log">
        <div class="window">
            <form action="reg.php" method="post">
                <h1>Регистрация</h1>
                <div class="l">
                    <p>Введите ФИО</p>
                    <input type="text" name="name">
                </div>
                <div class="l">
                    <p>Введите дату рождения (ДД.ММ.ГГГГ)</p>
                    <input type="text" name="date_b" onfocus="this.removeAttribute('readonly')">
                </div>
                <div class="l">
                    <p>Введите телефон</p>
                    <input type="text" name="tel" onfocus="this.removeAttribute('readonly')">
                </div>
                <div class="l">
                    <p>Придумайте логин</p>
                    <input type="text" name="login" onfocus="this.removeAttribute('readonly')">
                    <?php
                    if ($_SESSION['Message_login']) {
                        echo '<p class="msg">' . $_SESSION['Message_login'] . '</p>';
                    }
                    unset($_SESSION['Message_login']);
                    ?>
                </div>
                <div class="l">
                    <p>Придумайте пароль</p>
                    <input type="password" name="pass">
                </div>
                <div class="l">
                    <p>Повторите пароль</p>
                    <input type="password" name="pass_n">
                    <?php
                    if ($_SESSION['Message_pass']) {
                        echo '<p class="msg">' . $_SESSION['Message_pass'] . '</p>';
                    }
                    unset($_SESSION['Message_pass']);
                    ?>
                </div>
                <button class="next" type="submit">Зарегистрироваться </button> <br>
                <a class="link_log" href="log.php">Есть аккаунт? Авторизуйтесь</a>
            </form>
        </div>
    </div>
    <footer></footer>
</body>

</html>