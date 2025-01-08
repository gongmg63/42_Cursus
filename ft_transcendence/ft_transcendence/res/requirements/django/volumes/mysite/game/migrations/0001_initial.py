# Generated by Django 5.1.4 on 2025-01-08 04:24

import django.db.models.deletion
import django.utils.timezone
from django.conf import settings
from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
    ]

    operations = [
        migrations.CreateModel(
            name='GameResult',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('winner_score', models.PositiveIntegerField(verbose_name='승자 점수')),
                ('loser_score', models.PositiveIntegerField(verbose_name='패자 점수')),
                ('game_date', models.DateTimeField(default=django.utils.timezone.now, verbose_name='게임 날짜')),
                ('game_type', models.CharField(choices=[('1vs1', '1VS1'), ('tournament', 'Tournament'), ('final', 'Final')], max_length=50, verbose_name='게임 종류')),
                ('loser', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='lost_games', to=settings.AUTH_USER_MODEL)),
                ('winner', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='won_games', to=settings.AUTH_USER_MODEL)),
            ],
        ),
    ]
