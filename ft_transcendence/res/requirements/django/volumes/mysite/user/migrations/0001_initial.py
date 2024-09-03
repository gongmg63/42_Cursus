# Generated by Django 5.1 on 2024-09-02 14:42

import mysite.utils
from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='User',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('oauthid', models.IntegerField(unique=True, verbose_name='OAuth2.0')),
                ('nickname', models.CharField(max_length=20, unique=True, verbose_name='닉네임')),
                ('wins', models.PositiveIntegerField(default=0, verbose_name='승')),
                ('losses', models.PositiveIntegerField(default=0, verbose_name='패')),
                ('profile', models.ImageField(blank=True, upload_to=mysite.utils.uuid_name_upload_to)),
                ('friends', models.ManyToManyField(blank=True, related_name='friend_set', to='user.user', verbose_name='친구')),
            ],
            options={
                'verbose_name': '사용자',
                'verbose_name_plural': '사용자들',
            },
        ),
    ]
