<?php
session_start();
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <form enctype="multipart/form-data" action="script.php" method="POST">
        <?php
        if ($_SESSION['Message_no_full_data']) {
                echo '<p class="msg" style="color:red">' . $_SESSION['Message_no_full_data'] . '</p>';
            }
            unset($_SESSION['Message_no_full_data']);
        ?>
        <p>Введите имя</p><br>
        <input name="name" type="text"><br>
        <p>Введите адрес электронной почты</p><br>
        <input name="email" type="email"><br>
        <p>Выберите оценку</p><br>
        <select name="estimation">
            <option value="Не выбрана">Не выбрано</option>
            <option value="1">1</option>
            <option value="2">2</option>
            <option value="3">3</option>
            <option value="4">4</option>
            <option value="5">5</option>
        </select><br>
        <p>Введите отзыв</p><br>
        <input name="review" type="text"><br>
        <input name="img" type="file">
        <button type="submit">Отправить</button>
    </form>
</body>
</html>