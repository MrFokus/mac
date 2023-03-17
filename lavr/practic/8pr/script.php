<?php
    session_start();
    $form=$_POST;
    if(($form['name']!=NULL)&($form['email']!=NULL)){
    $file = 'review/review.txt';
    $string="\nПользователь: ".$form['name']."\n"."Почта: ".$form['email']."\n"."Оценка: ".$form['estimation']."\n"."Отзыв\n".$form['review'];
    $path = "img/".$_FILES['img']['name'];
    if (!preg_match('/^[A-Za-z]+.+$/u', $form['name']))
    $errors['name'] = 'should consist of two words!';
    if (filter_var($form['email'], FILTER_VALIDATE_EMAIL) != $form['email'])
    $errors['email'] = 'provide correct email!';
    var_dump($errors);
    file_put_contents($file, $string, FILE_APPEND | LOCK_EX);
    move_uploaded_file($_FILES['img']['tmp_name'],$path);
    header('Location: index.php');
    }
    else{
        $_SESSION['Message_no_full_data'] = "Поля имя и адрес элекстронной почты должны быть заполнены!";
        header('Location: index.php');
    }
?>